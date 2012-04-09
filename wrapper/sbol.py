import libsbol
import sys
from cStringIO import StringIO

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
    'Document',
    'DNASequence',
    'SequenceAnnotation',
    'DNAComponent',
    'Collection' )

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
    Like an ExtendableSBOLObjectArray, except it can't
    be added to manually. It's used as a proxy for the PointerArrays
    in a Document, which are automatically edited when SBOL objects
    are created or destroyed.
    '''

    def __init__(self, obj, num, nth):
        self.ptr = obj.ptr
        if isinstance(obj, Document):
            self.doc = obj
        else:
            self.doc = obj.doc

        # Each type of SBOL object has its own array functions,
        # which need to be set for the wrapper to work.
        self.get_num_fn = num
        self.get_nth_fn = nth

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
        obj = self.doc._proxy(ptr)
        return obj

    def __getslice__(self, *indices):
        "'implements 'array[start:end:step]'"
        return [self._getsingle_(n) for n in range(*indices)]

    def __iter__(self):
        "implements 'for obj in array:'"
        num = self.get_num_fn(self.ptr)
        for n in range(num):
            ptr = self.get_nth_fn(self.ptr, n)
            obj = self.doc._proxy(ptr)
            yield obj

    def __contains__(self, obj):
        "implements 'obj in array'"
        for candidate_obj in self:
            if candidate_obj == obj:
                return True
        return False

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

class ExtendableSBOLObjectArray(SBOLObjectArray):
    '''
    Wrapper around a libSBOLc PointerArray.
    It behaves like a standard Python list,
    but only for those operations a PointerArray
    supports. Notably, remove() hasn't been
    implemented yet.
    '''

    def __init__(self, obj, add, num, nth):
        SBOLObjectArray.__init__(self, obj, num, nth)
        self.add_fn = add

    def __iadd__(self, obj):
        "implements 'array += obj'"
        if obj in self:
            raise SBOLError('Duplicate obj %s' % obj)
        self.add_fn(self.ptr, obj.ptr)
        return self

    def append(self, obj):
        "implements 'array.append(obj)'"
        self.__iadd__(obj)

    def __extend__(self, obj_list):
        "implements 'array += obj_list'"
        for obj in obj_list:
            self += obj

class Document(object):
    'Wrapper around a libSBOLc Document'
    
    def __init__(self):
        # create document
        self.ptr = libsbol.createDocument()

        # create sequences array
        fns = (libsbol.getNumDNASequences,
               libsbol.getNthDNASequence)
        self.sequences = SBOLObjectArray(self, *fns)

        # create annotations array
        fns = (libsbol.getNumSequenceAnnotations,
               libsbol.getNthSequenceAnnotation)
        self.annotations = SBOLObjectArray(self, *fns)

        # create components array
        fns = (libsbol.getNumDNAComponents,
               libsbol.getNthDNAComponent)
        self.components = SBOLObjectArray(self, *fns)

        # create collections array
        fns = (libsbol.getNumCollections,
               libsbol.getNthCollection)
        self.collections = SBOLObjectArray(self, *fns)

        # create lists of Python proxy objects to keep them
        # from being garbage collected, and for looking up
        # objects from SWIG pointers
        self._sequences   = []
        self._annotations = []
        self._components  = []
        self._collections = []

    def __str__(self):
        return capture_stdout(libsbol.printDocument, self.ptr)

    def read(self, filename):
        libsbol.readDocument(self.ptr, filename)

    def write(self, filename):
        libsbol.writeDocument(self.ptr, filename)

    @property
    def num_sbol_objects(self):
        return len(self.sequences)   \
             + len(self.annotations) \
             + len(self.components)  \
             + len(self.collections)

    @property
    def uris(self):
        output = []
        for array in (self._sequences,
                      self._annotations,
                      self._components,
                      self._collections):
            for obj in array:
                output.append(obj.uri)
        return output

    def _proxy(self, ptr):
        'Find the Python proxy for an unknown pointer'
        for array in (self._sequences,
                      self._annotations,
                      self._components,
                      self._collections):
            for obj in array:
                if obj.ptr == ptr:
                    return obj
        return None

class DNASequence(object):
    'Wrapper around a libSBOLc DNASequence'
    
    def __init__(self, doc, uri):
        # create the C object
        self.ptr = libsbol.createDNASequence(doc.ptr, uri)
        if self.ptr == None:
            raise URIError("Duplicate URI '%s'" % uri)

        # register the Python proxy
        self.doc = doc
        self.doc._sequences.append(self)

    def __del__(self):
        if self.ptr:
            libsbol.deleteDNASequence(self.ptr)
        self.doc._sequences.remove(self)

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
    
    def __init__(self, doc, uri):
        # create the C object
        self.ptr = libsbol.createSequenceAnnotation(doc.ptr, uri)
        if self.ptr == None:
            raise URIError("Duplicate URI '%s'" % uri)

        # register the Python proxy
        self.doc = doc
        self.doc._annotations.append(self)

        # finish the Python proxy
        self.doc._annotations.append(self)
        fns = (libsbol.addPrecedesRelationship,
               libsbol.getNumPrecedes,
               libsbol.getNthPrecedes)
        self.precedes = ExtendableSBOLObjectArray(self, *fns)

    def __del__(self):
        if self.ptr:
            libsbol.deleteSequenceAnnotation(self.ptr)
        self.doc._annotations.remove(self)

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
        return self.doc._proxy(ptr)

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

class DNAComponent(object):
    'Wrapper around a libSBOLc DNAComponent'

    def __init__(self, doc, uri):
        # create the C object
        self.ptr = libsbol.createDNAComponent(doc.ptr, uri)
        if self.ptr == None:
            raise URIError("Duplicate URI '%s'" % uri)

        # register the Python proxy
        self.doc = doc
        self.doc._components.append(self)

        # finish the Python proxy
        fns = (libsbol.addSequenceAnnotation,
               libsbol.getNumSequenceAnnotationsFor,
               libsbol.getNthSequenceAnnotationFor)
        self.annotations = ExtendableSBOLObjectArray(self, *fns)

    def __del__(self):
        if self.ptr:
            libsbol.deleteDNAComponent(self.ptr)
        self.doc._components.remove(self)

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
        return self.doc._proxy(ptr)

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

class Collection(object):
    'Wrapper around a libSBOLc Collection'

    def __init__(self, doc, uri):
        # create the C object
        self.ptr = libsbol.createCollection(doc.ptr, uri)
        if self.ptr == None:
            raise URIError("Duplicate URI '%s'" % uri)

        # register the Python proxy
        self.doc = doc
        self.doc._collections.append(self)

        # finish the Python proxy
        fns = (libsbol.addDNAComponentToCollection,
               libsbol.getNumDNAComponentsIn,
               libsbol.getNthDNAComponentIn)
        self.components = ExtendableSBOLObjectArray(self, *fns)

    def __del__(self):
        if self.ptr:
            libsbol.deleteCollection(self.ptr)
        self.doc._collections.remove(self)

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

