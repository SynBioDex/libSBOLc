import libsbol
import sys
from cStringIO import StringIO
import weakref

__all__ = (
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
        self.sbol_objects = []

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
        for obj in self.sbol_objects:
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

# todo PointerArray class so you can do slicing, append, etc.

class DNASequence(object):
    'Implements the SBOL Core DNASequence object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createDNASequence(uri)
        ALL_SBOL_OBJECTS.add(self)

    def __del__(self):
        print '%s.__del__' % self.uri
        libsbol.deleteDNASequence(self.ptr)

    def __str__(self):
        return capture_stdout(libsbol.printDNASequence, self.ptr, 0)

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
    'Implements the SBOL Core SequenceAnnotation object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createSequenceAnnotation(uri)
        ALL_SBOL_OBJECTS.add(self)

    def __del__(self):
        print '%s.__del__' % self.uri
        libsbol.deleteSequenceAnnotation(self.ptr)

    def __str__(self):
        return capture_stdout(libsbol.printSequenceAnnotation, self.ptr, 0)

    @property
    def uri(self):
        return libsbol.getSequenceAnnotationURI(self.ptr)

    @property
    def start(self):
        return libsbol.getSequenceAnnotationNucleotides(self.ptr)

    @start.setter
    def start(self, index):
        libsbol.setSequenceAnnotationStart(self.ptr, index)
        
    @property
    def end(self):
        return libsbol.getSequenceAnnotationEnd(self.ptr)

    @end.setter
    def end(self, index):
        libsbol.setSequenceAnnotationEnd(self.ptr, index)

    @property
    def strand(self):
        return libsbol.getSequenceAnnotationStrand(self.ptr)

    # doesn't appear to work
    @strand.setter
    def strand(self, polarity):
        libsbol.setSequenceAnnotationStrand(self.ptr, polarity)

    @property
    def subcomponent(self):
        ptr = libsbol.getSequenceAnnotationSubComponent(self.ptr)
        return ALL_SBOL_OBJECTS.find(ptr)

    @subcomponent.setter
    def subcomponent(self, com):
        libsbol.setSequenceAnnotationSubComponent(self.ptr, com)

    # can this be done with a decorator?
    def add_precedes(self, downstream):
        libsbol.addPrecedesRelationship(self.ptr, downstream.ptr)

    @property
    def precedes(self):
        precedes = []
        num = libsbol.getNumPrecedes(self.ptr)
        for n in range(num):
            ptr = libsbol.getNthPrecedes(self.ptr, n)
            precedes.append( ALL_SBOL_OBJECTS.find(ptr) )
        return precedes

class DNAComponent(object):
    'Implements the SBOL Core DNAComponent object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createDNAComponent(uri)
        ALL_SBOL_OBJECTS.add(self)

    def __del__(self):
        print '%s.__del__' % self.uri
        libsbol.deleteDNAComponent(self.ptr)
            
    def __str__(self):
        return capture_stdout(libsbol.printDNAComponent, self.ptr, 0)

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

    @property
    def annotations(self):
        annotations = []
        num = libsbol.getNumSequenceAnnotationsFor(self.ptr)
        for n in range(num):
            ptr = libsbol.getNthSequenceAnnotationFor(self.ptr, n)
            annotations.append( ALL_SBOL_OBJECTS.find(ptr) )
        return annotations

    @display_id.setter
    def display_id(self, id):
        libsbol.setDNAComponentDisplayID(self.ptr, id)

    @name.setter
    def name(self, name):
        libsbol.setDNAComponentName(self.ptr, name)

    @description.setter
    def description(self, descr):
        libsbol.setDNAComponentDescription(self.ptr, descr)

    @sequence.setter
    def sequence(self, seq):
        libsbol.setDNAComponentSequence(self.ptr, seq.ptr)

    # can this be done with a property?
    def add_annotation(self, ann):
        libsbol.addSequenceAnnotation(self.ptr, ann.ptr)

    # todo remove_annotation?

class Collection(object):
    'Implements the SBOL Core Collection object'

    def __init__(self, uri):
        object.__init__(self)
        self.ptr = libsbol.createCollection(uri)
        ALL_SBOL_OBJECTS.add(self)

    def __del__(self):
        print '%s.__del__' % self.uri
        libsbol.deleteCollection(self.ptr)

    def __str__(self):
        return captiure_stdout(libsbol.printCollection, self.ptr, 0)

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

    @property
    def components(self):
        components = []
        num = libsbol.getNumDNAComponentsIn(self.ptr)
        for n in range(num):
            ptr = libsbol.getNthDNAComponentIn(self.ptr, n)
            components.append( ALL_SBOL_OBJECTS.find(ptr) )
        return components

    @display_id.setter
    def display_id(self, id):
        libsbol.setCollectionDisplayID(self.ptr, id)

    @name.setter
    def name(self, name):
        libsbol.setCollectionName(self.ptr, name)

    @description.setter
    def description(self, descr):
        libsbol.setCollectionDescription(self.ptr, descr)

    # can this be done with a decorator?
    def add_component(self, com):
        libsbol.addDNAComponentToCollection(com.ptr, self.ptr)

