import libsbol
import sys
from cStringIO import StringIO
import weakref

class SBOLError(Exception):     'Problem with SBOL'
class InternalError(SBOLError): 'Encountered a bug'
class URIError(SBOLError):      'Invalid URI'
class PositionError(SBOLError): 'Invalid position'
class StrandError(SBOLError):   'Invalid strand polarity'

__all__ = (
    'SBOLError',
    'InternalError',
    'URIError',
    'PositionError',
    'StrandError',
    'DNASequence',
    'SequenceAnnotation',
    'DNAComponent',
    'Collection' )

class SBOLObjectRegistry(object):
    '''
    Each SBOL object has a ptr attribute that lets
    you get the SWIG pointer to it. But since pointers are
    read-only (and unhashable), you need a workaround
    to go the other way, from pointer --> object.
    '''

    def __init__(self):
        # todo rename to something with ref in it
        self.sbol_objects = []

    def __str__(self):
        output = []
        output.append('[')
        for ref in self.sbol_objects[:-1]:
            if ref != None:
                output.append( ref().__repr__() )
                output.append(', ')
        output.append(self.sbol_objects[-1]().__repr__())
        output.append(']')
        return ''.join(output)

    def add(self, obj):
        '''
        Create and store a weak reference to obj. It works
        like a regular reference, except it doesn't prevent
        obj from being garbage collected. That's important
        because otherwise obj.__del__ would never be called.
        Plus, when obj is garbage collected the callback
        will remove the ref.
        '''
        callback = self.sbol_objects.remove
        ref = weakref.ref(obj, callback)
        self.sbol_objects.append(ref)

    def find(self, ptr):
        'Get the SBOL object pointed to by ptr.'
        for ref in self.sbol_objects:
            obj = ref()
            if obj.ptr == ptr:
                return obj
        return None

ALL_SBOL_OBJECTS = SBOLObjectRegistry()

def capture_stdout(fn, *args, **kwargs):
    '''
    The SBOL print functions use printf() to print directly
    to stdout; this captures that output and returns it for
    use in Python's __str__ methods.
    '''
    backup = sys.stdout
    sys.stdout = StringIO()
    fn(*args, **kwargs)
    output = sys.stdout.getvalue()
    sys.stdout.close()
    sys.stdout = backup
    return output

class SBOLObjectArray(object):
    '''
    Wrapper around a libSBOLc PointerArray.
    It behaves like a standard Python list,
    but only for those operations a PointerArray
    supports. Notably, remove() hasn't been
    implemented yet.
    '''

    def __init__(self, ptr, add, num, nth):
        # Each type of SBOL object has its own array functions,
        # which need to be set for the wrapper to work.
        self.ptr        = ptr
        self.add_fn     = add
        self.get_num_fn = num
        self.get_nth_fn = nth

        # These references aren't used for anything so far,
        # but they keep Python from garbage collecting the
        # objects corresponding to pointers in the array.
        self.refs = set()

    def __len__(self):
        "implements 'len(array)'"
        return self.get_num_fn(self.ptr)

    def __getitem__(self, key):
        "distinguishes 'array[index]' from 'array[start:end:step]'"
        if isinstance(key, slice):
            indices = key.indices( len(self) )
            return self.__getslice__(indices)
        else: # assume int-like object
            if key < 0: # indexed from end
                key += len(self)
            return self._getsingle_(key)

    def _getsingle_(self, index):
        "implements 'array[index]'"
        num = self.get_num_fn(self.ptr)
        if index >= num:
            raise IndexError
        ptr = self.get_nth_fn(self.ptr, index)
        obj = ALL_SBOL_OBJECTS.find(ptr)
        return obj

    def __getslice__(self, *indices):
        "'implements 'array[start:end:step]'"
        return [self._getsingle_(n) for n in range(*indices)]

    def __iter__(self):
        "implements 'for obj in array:'"
        num = self.get_num_fn(self.ptr)
        for n in range(num):
            ptr = self.get_nth_fn(self.ptr, n)
            obj = ALL_SBOL_OBJECTS.find(ptr)
            yield obj

    def __contains__(self, obj):
        "implements 'obj in array'"
        for candidate_obj in self:
            if candidate_obj == obj:
                return True
        return False

    def __iadd__(self, obj):
        "implements 'array += obj'"
        if obj in self:
            raise SBOLError('Duplicate obj %s' % obj)
        self.refs.add(obj)
        self.add_fn(self.ptr, obj.ptr)
        return self

    def append(self, obj):
        "implements 'array.append(obj)'"
        self.__iadd__(obj)

    def __extend__(self, obj_list):
        "implements 'array += obj_list'"
        for obj in obj_list:
            self += obj

    def __str__(self):
        "implements 'print array'"
        if len(self) == 0:
            return '[]'
        output = []
        output.append('[')
        for obj in self[:-1]:
            output.append(obj.__repr__())
            output.append(', ')
        output.append(self[-1].__repr__())
        output.append(']')
        return ''.join(output)

    def __repr__(self):
        "implements 'array' (print in the interpreter)"
        return self.__str__()

class DNASequence(object):
    'Wrapper around a libSBOLc DNASequence'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createDNASequence(uri)
        if not self.ptr:
            raise URIError("Duplicate URI '%s'" % uri)
        ALL_SBOL_OBJECTS.add(self)

    def __del__(self):
        if self.ptr:
            libsbol.deleteDNASequence(self.ptr)

    def __str__(self):
        return capture_stdout(libsbol.printDNASequence, self.ptr, 0)

    def __repr__(self):
        return "<%s uri='%s'>" % (self.__class__.__name__, self.uri)

    @property
    def uri(self):
        return libsbol.getDNASequenceURI(self.ptr)

    @property
    def nucleotides(self):
        return libsbol.getDNASequenceNucleotides(self.ptr)

    @nucleotides.setter
    def nucleotides(self, value):
        libsbol.setDNASequenceNucleotides(self.ptr, value)

class SequenceAnnotation(object):
    'Wrapper around a libSBOLc SequenceAnnotation'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createSequenceAnnotation(uri)
        if not self.ptr:
            raise URIError("Duplicate URI '%s'" % uri)
        ALL_SBOL_OBJECTS.add(self)
        fns = (libsbol.addPrecedesRelationship,
               libsbol.getNumPrecedes,
               libsbol.getNthPrecedes)
        self.precedes = SBOLObjectArray(self.ptr, *fns)

        # This prevents the Python proxies of C structs pointed to
        # by this SequenceAnnotation from being garbage collected.
        self.refs = set()

    def __del__(self):
        if self.ptr:
            libsbol.deleteSequenceAnnotation(self.ptr)

    def __str__(self):
        return capture_stdout(libsbol.printSequenceAnnotation, self.ptr, 0)

    def __repr__(self):
        return "<%s uri='%s'>" % (self.__class__.__name__, self.uri)

    @property
    def uri(self):
        return libsbol.getSequenceAnnotationURI(self.ptr)

    @property
    def start(self):
        start = libsbol.getSequenceAnnotationStart(self.ptr)
        if start == -1:
            return None
        else:
            return start

    @property
    def end(self):
        end = libsbol.getSequenceAnnotationEnd(self.ptr)
        if end == -1:
            return None
        else:
            return end

    @property
    def strand(self):
        polarity = libsbol.getSequenceAnnotationStrand(self.ptr)
        if polarity == libsbol.STRAND_FORWARD:
            return '+'
        elif polarity == libsbol.STRAND_BIDIRECTIONAL:
            return '*'
        elif polarity == libsbol.STRAND_REVERSE:
            return '-'
        else:
            raise InternalError('Got invalid strand polarity %i' % polarity )

    @property
    def subcomponent(self):
        ptr = libsbol.getSequenceAnnotationSubComponent(self.ptr)
        return ALL_SBOL_OBJECTS.find(ptr)

    @start.setter
    def start(self, index):
        if index == None:
            index = -1
        elif index < 0:
            raise PositionError('Negative position %i' % index)
        libsbol.setSequenceAnnotationStart(self.ptr, index)

    @end.setter
    def end(self, index):
        if index == None:
            index = -1
        elif index < 0:
            raise PositionError('Negative position %i' % index)
        libsbol.setSequenceAnnotationEnd(self.ptr, index)

    @strand.setter
    def strand(self, polarity):
        if polarity == '+':
            polarity = libsbol.STRAND_FORWARD
        elif polarity == '*':
            polarity = libsbol.STRAND_BIDIRECTIONAL
        elif polarity == '-':
            polarity = libsbol.STRAND_REVERSE
        else:
            raise StrandError('Invalid polarity %s' % polarity)
        libsbol.setSequenceAnnotationStrand(self.ptr, polarity)

    @subcomponent.setter
    def subcomponent(self, com):
        libsbol.setSequenceAnnotationSubComponent(self.ptr, com.ptr)
        self.refs.add(com)

class DNAComponent(object):
    'Wrapper around a libSBOLc DNAComponent'

    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createDNAComponent(uri)
        if not self.ptr:
            raise URIError("Duplicate URI '%s'" % uri)
        ALL_SBOL_OBJECTS.add(self)
        fns = (libsbol.addSequenceAnnotation,
               libsbol.getNumSequenceAnnotationsFor,
               libsbol.getNthSequenceAnnotationFor)
        self.annotations = SBOLObjectArray(self.ptr, *fns)

        # This prevents the Python proxies of C structs pointed to
        # by this DNAComponent from being garbage collected.
        self.refs = set()

    def __del__(self):
        if self.ptr:
            libsbol.deleteDNAComponent(self.ptr)

    def __str__(self):
        return capture_stdout(libsbol.printDNAComponent, self.ptr, 0)

    def __repr__(self):
        return "<%s uri='%s'>" % (self.__class__.__name__, self.uri)

    @property
    def uri(self):
        return libsbol.getDNAComponentURI(self.ptr)

    @property
    def display_id(self):
        return libsbol.getDNAComponentDisplayID(self.ptr)

    @property
    def name(self):
        return libsbol.getDNAComponentName(self.ptr)

    @property
    def description(self):
        return libsbol.getDNAComponentDescription(self.ptr)

    @property
    def sequence(self):
        ptr = libsbol.getDNAComponentSequence(self.ptr)
        return ALL_SBOL_OBJECTS.find(ptr)

    @display_id.setter
    def display_id(self, displayid):
        libsbol.setDNAComponentDisplayID(self.ptr, displayid)

    @name.setter
    def name(self, name):
        libsbol.setDNAComponentName(self.ptr, name)

    @description.setter
    def description(self, descr):
        libsbol.setDNAComponentDescription(self.ptr, descr)

    @sequence.setter
    def sequence(self, seq):
        libsbol.setDNAComponentSequence(self.ptr, seq.ptr)
        self.refs.add(seq)

class Collection(object):
    'Wrapper around a libSBOLc Collection'

    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createCollection(uri)
        if not self.ptr:
            raise URIError("Duplicate URI '%s'" % uri)
        ALL_SBOL_OBJECTS.add(self)
        fns = (libsbol.addDNAComponentToCollection,
               libsbol.getNumDNAComponentsIn,
               libsbol.getNthDNAComponentIn)
        self.components = SBOLObjectArray(self.ptr, *fns)

    def __del__(self):
        if self.ptr:
            libsbol.deleteCollection(self.ptr)

    def __str__(self):
        return capture_stdout(libsbol.printCollection, self.ptr, 0)

    def __repr__(self):
        return "<%s uri='%s'>" % (self.__class__.__name__, self.uri)

    @property
    def uri(self):
        return libsbol.getCollectionURI(self.ptr)

    @property
    def display_id(self):
        return libsbol.getCollectionDisplayID(self.ptr)

    @property
    def name(self):
        return libsbol.getCollectionName(self.ptr)

    @property
    def description(self):
        return libsbol.getCollectionDescription(self.ptr)

    @display_id.setter
    def display_id(self, displayid):
        libsbol.setCollectionDisplayID(self.ptr, displayid)

    @name.setter
    def name(self, name):
        libsbol.setCollectionName(self.ptr, name)

    @description.setter
    def description(self, descr):
        libsbol.setCollectionDescription(self.ptr, descr)

