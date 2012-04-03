from sbol_swig import *

__all__ = (
'SBOLError',
'MethodError', 'ArgumentError', 'ReturnError',
'DNASequence', 'SequenceAnnotation',
'DNAComponent', 'Collection'
)

class SBOLError(Exception):     'Error in the SBOL SWIG wrapper'
class MethodError(SBOLError):   'Incorrect method use'
class ArgumentError(SBOLError): 'Method called with incorrect pointer'
class ReturnError(SBOLError):   'Method returned incorrect pointer'

class PointerArray(list):
    def __getitem__(self, index):
        item = getNthPointerInArray(self.ptr, index)
        if not item:
            raise ReturnError
        return item

    def __setitem__(self, index):
        raise MethodError

    def __getslice__(self, start, end):
        if getNumPointersInArray(self.ptr) <= end:
            raise ArgumentError
        pointers = []
        # check that the indexing is right
        for n in range(end - start):
            pointer = getNthPointerInArray(self.ptr, n)
            pointers.append(pointer)
        return pointers

    def append(self, pointer):
        # check type here?
        insertPointerIntoArray(self.ptr, pointer)

class DNASequence(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNASequence(uri)

    def __del__(self):
        deleteDNASequence(self.ptr)
        object.__del__(self)

    def getURI(self):
        return getDNASequenceURI(self.ptr)

    def setURI(self, uri):
        setDNASequenceURI(self.ptr, uri)

class SequenceAnnotation(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createSequenceAnnotation(uri)

    def __del__(self):
        deleteSequenceAnnotation(self.ptr)
        object.__del__(self)

    def getURI(self):
        return getSequenceAnnotationURI(self.ptr)

    def setURI(self, uri):
        setSequenceAnnotationURI(self.ptr, uri)

class DNAComponent(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNAComponent(uri)

    def __del__(self):
        deleteDNAComponent(self.ptr)
        object.__del__(self)

    def getURI(self):
        return getDNAComponentURI(self.ptr)

    def setURI(self, uri):
        setDNAComponentURI(self.ptr, uri)

class Collection(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createCollection(uri)

    def __del__(self):
        deleteCollection(self.ptr)
        object.__del__(self)

    def getURI(self):
        return getCollectionURI(self.ptr)

    def setURI(self, uri):
        setCollectionURI(self.ptr, uri)

