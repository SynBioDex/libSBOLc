from sbol_swig import *
import sys
from cStringIO import StringIO

__all__ = (
    'DNASequence',
    'SequenceAnnotation',
    'DNAComponent',
    'Collection' )

############################################################
# The sbol objects each have a ptr attribute that lets
# you get their pointer. But since the pointers are
# read-only (and unhashable), you need a workaround
# to go the other way, from pointer --> object.
#
ALL_SBOL_OBJECTS = []
#
def register_sbol_object(obj):
    ALL_SBOL_OBJECTS.append((obj, obj.ptr))
#
def retrieve_sbol_object(ptr):
    for (obj, candidate_ptr) in ALL_SBOL_OBJECTS:
        if candidate_ptr == ptr:
            return obj
    return None

def remove_sbol_object(obj):
    for candidate in ALL_SBOL_OBJECTS:
        if candidate[0] == obj:
            ALL_SBOL_OBJECTS.remove(candidate)
            return

#
############################################################

def return_stdout(fn):
    '''
    The SBOL print functions use printf() to print directly
    # to stdout; this is a workaround that captures that
    # output so Python can use it in __str__ methods.
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

class DNASequence(object):
    'Implements the SBOL Core DNASequence object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNASequence(uri)
        register_sbol_object(self)

    def __del__(self):
        remove_sbol_object(self)
        deleteDNASequence(self.ptr)

    @return_stdout
    def __str__(self):
        printDNASequence(self.ptr, 0)

    def get_uri(self):
        return getDNASequenceURI(self.ptr)

    def set_nucleotides(self, nt):
        setDNASequenceNucleotides(self.ptr, nt)

    def get_nucleotides(self):
        return getDNASequenceNucleotides(self.ptr)

class SequenceAnnotation(object):
    'Implements the SBOL Core SequenceAnnotation object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createSequenceAnnotation(uri)
        register_sbol_object(self)

    def __del__(self):
        remove_sbol_object(self)
        deleteSequenceAnnotation(self.ptr)

    @return_stdout
    def __str__(self):
        printSequenceAnnotation(self.ptr, 0)

    def get_uri(self):
        return getSequenceAnnotationURI(self.ptr)

    def set_start(self, index):
        setSequenceAnnotationStart(self.ptr, index)
        
    def get_start(self):
        return getSequenceAnnotationNucleotides(self.ptr)

    def set_end(self, index):
        setSequenceAnnotationEnd(self.ptr, index)

    def get_end(self):
        return getSequenceAnnotationEnd(self.ptr)

    def set_strand(self, polarity):
        setSequenceAnnotationStrand(self.ptr, polarity)

    def get_strand(self):
        return getSequenceAnnotationStrand(self.ptr)

    def set_subcomponent(self, com):
        setSequenceAnnotationSubComponent(self.ptr, com)

    def get_subcomponent(self):
        ptr = getSequenceAnnotationSubComponent(self.ptr)
        return retrieve_sbol_object(ptr)

    def add_precedes(self, downstream):
        addPrecedesRelationship(self.ptr, downstream.ptr)

    def get_precedes(self):
        precedes = []
        num = getNumPrecedes(self.ptr)
        for n in range(num):
            ptr = getNthPrecedes(self.ptr, n)
            precedes.append( retrieve_sbol_object(ptr) )
        return precedes

class DNAComponent(object):
    'Implements the SBOL Core DNAComponent object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNAComponent(uri)
        register_sbol_object(self)

    def __del__(self):
        remove_sbol_object(self)
        deleteDNAComponent(self.ptr)
            
    @return_stdout
    def __str__(self):
        printDNAComponent(self.ptr, 0)

    def get_uri(self):
        return getDNAComponentURI(self.ptr)

    def set_display_id(self, id):
        setDNAComponentDisplayID(self.ptr, id)

    def get_display_id(self):
        return getDNAComponentDisplayID(self.ptr)

    def set_name(self, name):
        setDNAComponentName(self.ptr, name)

    def get_name(self):
        return getDNAComponentName(self.ptr)

    def set_description(self, descr):
        setDNAComponentDescription(self.ptr, descr)

    def get_name(self):
        return getDNAComponentName(self.ptr)

    def set_sequence(self, seq):
        setDNAComponentSequence(self.ptr, seq.ptr)

    def get_sequence(self):
        ptr = getDNAComponentSequence(self.ptr)
        return retrieve_sbol_object(ptr)

    def add_annotation(self, ann):
        addSequenceAnnotation(self.ptr, ann.ptr)

    def get_annotations(self):
        annotations = []
        num = getNumSequenceAnnotationsFor(self.ptr)
        for n in range(num):
            ptr = getNthSequenceAnnotationFor(self.ptr, n)
            annotations.append( retrieve_sbol_object(ptr) )
        return annotations

    # todo remove_annotation?

class Collection(object):
    'Implements the SBOL Core Collection object'

    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createCollection(uri)
        register_sbol_object(self)

    # why does this throw an exception during shutdown?
    def __del__(self):
        remove_sbol_object(self)
        try:
            deleteCollection(self.ptr)
        except TypeError: # TypeError("'NoneType' object is not callable",)
            pass

    @return_stdout
    def __str__(self):
        printCollection(self.ptr, 0)

    def get_uri(self):
        return getCollectionURI(self.ptr)

    def set_display_id(self, id):
        setCollectionDisplayID(self.ptr, id)

    def get_display_id(self):
        return getCollectionDisplayID(self.ptr)

    def set_name(self, name):
        setCollectionName(self.ptr, name)

    def get_name(self):
        return getCollectionName(self.ptr)

    def set_description(self, descr):
        setCollectionDescription(self.ptr, descr)

    def get_description(self):
        return getCollectionDescription(self.ptr)

    def add_component(self, com):
        addDNAComponentToCollection(com.ptr, self.ptr)

    def get_components(self):
        components = []
        num = getNumDNAComponentsIn(self.ptr)
        for n in range(num):
            ptr = getNthDNAComponentIn(self.ptr, n)
            components.append( retrieve_sbol_object(ptr) )
        return components

