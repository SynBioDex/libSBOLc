import libsbol
import sys
from cStringIO import StringIO
import atexit

__all__ = (
    'STRAND_FORWARD',
    'STRAND_BIDIRECTIONAL',
    'STRAND_REVERSE',
    'DNASequence',
    'SequenceAnnotation',
    'DNAComponent',
    'Collection' )

@atexit.register
def check_cleanup():
    print 'sbol objects orphaned in python:', len(ALL_SBOL_OBJECTS)
    print 'sbol objects orphaned in c:', sbol_swig.getNumSBOLObjects()

class WrapperError(Exception): 'Problem with the SBOL wrapper'

############################################################
# The sbol objects each have a ptr attribute that lets
# you get their pointer. But since the pointers are
# read-only (and unhashable), you need a workaround
# to go the other way, from pointer --> object.

ALL_SBOL_OBJECTS = []

def register_sbol_object(obj):
    ALL_SBOL_OBJECTS.append(obj)

def retrieve_sbol_object(ptr):
    for obj in ALL_SBOL_OBJECTS:
        if obj.ptr == ptr:
            return obj
    return None

def remove_sbol_object(obj):
    if ALL_SBOL_OBJECTS:
        ALL_SBOL_OBJECTS.remove(obj)

############################################################

def return_stdout(fn):
    '''
    The SBOL print functions use printf() to print directly
    to stdout; this is a workaround that captures that
    output so Python can use it in __str__ methods.
    '''
    def decorated_fn(*args, **kwargs):
        'Redirect stdout to a str and return it'
        backup = sys.stdout
        sys.stdout = StringIO()
        fn(*args, **kwargs)
        output = sys.stdout.getvalue()
        sys.stdout.close()
        sys.stdout = backup
        return output
    return decorated_fn

# todo PointerArray class so you can do slicing, append, etc.

class DNASequence(object):
    'Implements the SBOL Core DNASequence object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNASequence(uri)
        register_sbol_object(self)

    def __del__(self):
        #remove_sbol_object(self)
        try:
            sbol_swig.deleteDNASequence(self.ptr)
        except TypeError:
            pass

    @return_stdout
    def __str__(self):
        sbol_swig.printDNASequence(self.ptr, 0)

    @property
    def uri(self):
        return sbol_swig.getDNASequenceURI(self.ptr)

    @property
    def nucleotides(self):
        return sbol_swig.getDNASequenceNucleotides(self.ptr)

    @nucleotides.setter
    def nucleotides(self, value):
        sbol_swig.setDNASequenceNucleotides(self.ptr, value)

class SequenceAnnotation(object):
    'Implements the SBOL Core SequenceAnnotation object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createSequenceAnnotation(uri)
        register_sbol_object(self)

    def __del__(self):
        #remove_sbol_object(self)
        try:
            sbol_swig.deleteSequenceAnnotation(self.ptr)
        except TypeError:
            pass

    @return_stdout
    def __str__(self):
        sbol_swig.printSequenceAnnotation(self.ptr, 0)

    @property
    def uri(self):
        return sbol_swig.getSequenceAnnotationURI(self.ptr)

    @property
    def start(self):
        return sbol_swig.getSequenceAnnotationNucleotides(self.ptr)

    @start.setter
    def start(self, index):
        sbol_swig.setSequenceAnnotationStart(self.ptr, index)
        
    @property
    def end(self):
        return sbol_swig.getSequenceAnnotationEnd(self.ptr)

    @end.setter
    def end(self, index):
        sbol_swig.setSequenceAnnotationEnd(self.ptr, index)

    @property
    def strand(self):
        return sbol_swig.getSequenceAnnotationStrand(self.ptr)

    # doesn't appear to work
    @strand.setter
    def strand(self, polarity):
        sbol_swig.setSequenceAnnotationStrand(self.ptr, polarity)

    @property
    def subcomponent(self):
        ptr = sbol_swig.getSequenceAnnotationSubComponent(self.ptr)
        return retrieve_sbol_object(ptr)

    @subcomponent.setter
    def subcomponent(self, com):
        sbol_swig.setSequenceAnnotationSubComponent(self.ptr, com)

    # can this be done with a decorator?
    def add_precedes(self, downstream):
        sbol_swig.addPrecedesRelationship(self.ptr, downstream.ptr)

    @property
    def precedes(self):
        precedes = []
        num = sbol_swig.getNumPrecedes(self.ptr)
        for n in range(num):
            ptr = sbol_swig.getNthPrecedes(self.ptr, n)
            precedes.append( retrieve_sbol_object(ptr) )
        return precedes

class DNAComponent(object):
    'Implements the SBOL Core DNAComponent object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNAComponent(uri)
        register_sbol_object(self)

    def __del__(self):
        #remove_sbol_object(self)
        try:
            sbol_swig.deleteDNAComponent(self.ptr)
        except TypeError:
            pass
            
    @return_stdout
    def __str__(self):
        sbol_swig.printDNAComponent(self.ptr, 0)

    @property
    def uri(self):
        return sbol_swig.getDNAComponentURI(self.ptr)

    @property
    def display_id(self):
        return sbol_swig.getDNAComponentDisplayID(self.ptr)

    @property
    def name(self):
        return sbol_swig.getDNAComponentName(self.ptr)

    @property
    def description(self):
        return sbol_swig.getDNAComponentDescription(self.ptr)

    @property
    def sequence(self):
        ptr = sbol_swig.getDNAComponentSequence(self.ptr)
        return retrieve_sbol_object(ptr)

    @property
    def annotations(self):
        annotations = []
        num = sbol_swig.getNumSequenceAnnotationsFor(self.ptr)
        for n in range(num):
            ptr = sbol_swig.getNthSequenceAnnotationFor(self.ptr, n)
            annotations.append( retrieve_sbol_object(ptr) )
        return annotations

    @display_id.setter
    def display_id(self, id):
        sbol_swig.setDNAComponentDisplayID(self.ptr, id)

    @name.setter
    def name(self, name):
        sbol_swig.setDNAComponentName(self.ptr, name)

    @description.setter
    def description(self, descr):
        sbol_swig.setDNAComponentDescription(self.ptr, descr)

    @sequence.setter
    def sequence(self, seq):
        sbol_swig.setDNAComponentSequence(self.ptr, seq.ptr)

    # can this be done with a property?
    def add_annotation(self, ann):
        sbol_swig.addSequenceAnnotation(self.ptr, ann.ptr)

    # todo remove_annotation?

class Collection(object):
    'Implements the SBOL Core Collection object'

    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createCollection(uri)
        register_sbol_object(self)

    # why does this throw an exception during shutdown?
    def __del__(self):
        #remove_sbol_object(self)
        try:
            sbol_swig.deleteCollection(self.ptr)
        except TypeError: # TypeError("'NoneType' object is not callable",)
            pass

    @return_stdout
    def __str__(self):
        sbol_swig.printCollection(self.ptr, 0)

    @property
    def uri(self):
        return sbol_swig.getCollectionURI(self.ptr)

    @property
    def display_id(self):
        return sbol_swig.getCollectionDisplayID(self.ptr)

    @property
    def name(self):
        return sbol_swig.getCollectionName(self.ptr)

    @property
    def description(self):
        return sbol_swig.getCollectionDescription(self.ptr)

    @property
    def components(self):
        components = []
        num = sbol_swig.getNumDNAComponentsIn(self.ptr)
        for n in range(num):
            ptr = sbol_swig.getNthDNAComponentIn(self.ptr, n)
            components.append( retrieve_sbol_object(ptr) )
        return components

    @display_id.setter
    def display_id(self, id):
        sbol_swig.setCollectionDisplayID(self.ptr, id)

    @name.setter
    def name(self, name):
        sbol_swig.setCollectionName(self.ptr, name)

    @description.setter
    def description(self, descr):
        sbol_swig.setCollectionDescription(self.ptr, descr)

    # can this be done with a decorator?
    def add_component(self, com):
        sbol_swig.addDNAComponentToCollection(com.ptr, self.ptr)

