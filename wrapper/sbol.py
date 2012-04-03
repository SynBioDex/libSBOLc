import sbol_swig

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
        item = sbol_swig.getNthPointerInArray(self.ptr, index)
        if not item:
            raise ReturnError
        return item

    def __setitem__(self, index):
        raise MethodError

    def __getslice__(self, start, end):
        if sbol_swig.getNumPointersInArray(self.ptr) <= end:
            raise ArgumentError
        pointers = []
        # check that the indexing is right
        for n in range(end - start):
            pointer = sbol_swig.getNthPointerInArray(self.ptr, n)
            pointers.append(pointer)
        return pointers

    def append(self, pointer):
        # check type here?
        sbol_swig.insertPointerIntoArray(self.ptr, pointer)

class DNASequence(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNASequence(uri)

    def __del__(self):
        sbol_swig.deleteDNASequence(self.ptr)
        object.__del__(self)

    def getURI(self):
        return sbol_swig.getDNASequenceURI(self.ptr)

    def setURI(self, uri):
        sbol_swig.setDNASequenceURI(self.ptr, uri)

class SequenceAnnotation(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createSequenceAnnotation(uri)

    def __del__(self):
        sbol_swig.deleteSequenceAnnotation(self.ptr)
        object.__del__(self)

    def getURI(self):
        return sbol_swig.getSequenceAnnotationURI(self.ptr)

    def setURI(self, uri):
        sbol_swig.setSequenceAnnotationURI(self.ptr, uri)

class DNAComponent(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNAComponent(uri)

    def __del__(self):
        sbol_swig.deleteDNAComponent(self.ptr)
        object.__del__(self)

    def getURI(self):
        return sbol_swig.getDNAComponentURI(self.ptr)

    def setURI(self, uri):
        sbol_swig.setDNAComponentURI(self.ptr, uri)

class Collection(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createCollection(uri)

    def __del__(self):
        sbol_swig.deleteCollection(self.ptr)
        object.__del__(self)

    def getURI(self):
        return sbol_swig.getCollectionURI(self.ptr)

    def setURI(self, uri):
        sbol_swig.setCollectionURI(self.ptr, uri)

