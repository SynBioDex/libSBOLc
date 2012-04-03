from sbol_swig import *
import sys
from cStringIO import StringIO

__all__ = (
    'DNASequence',
    'SequenceAnnotation',
    'DNAComponent',
    'Collection' )

def return_stdout(fn):
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
        self.ptr.obj = self

    def __del__(self):
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
        self.ptr.obj = self

    def __del__(self):
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
        return getSequenceAnnotationSubComponent(self.ptr).obj

    def add_precedes(self, downstream):
        addPrecedesRelationship(self.ptr, downstream.ptr)

    def get_precedes(self):
        precedes = []
        num = getNumPrecedes(self.ptr)
        for n in range(num):
            ptr = getNthPrecedes(self.ptr, n)
            precedes.append(ptr.obj)
        return precedes

class DNAComponent(object):
    'Implements the SBOL Core DNAComponent object'
    
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNAComponent(uri)
        self.ptr.obj = self

    def __del__(self):
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
        return getDNAComponentSequence(self.ptr).obj

    def add_annotation(self, ann):
        addSequenceAnnotation(self.ptr, ann.ptr)

    def get_annotations(self):
        annotations = []
        num = getNumSequenceAnnotationsFor(self.ptr)
        for n in range(num):
            ptr = getNthSequenceAnnotationFor(self.ptr, n)
            annotations.append(ptr.obj)
        return annotations

    # todo remove_annotation?

class Collection(object):
    'Implements the SBOL Core Collection object'

    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createCollection(uri)
        self.ptr.obj = self

    # why does this throw an exception during shutdown?
    def __del__(self):
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
            components.append(ptr.obj)
        return components

if __name__ == '__main__':
    c1  = Collection('collection1')
    dc1 = DNAComponent('component1')
    ds1 = DNASequence('sequence1')
    print c1
    print dc1
    print ds1

