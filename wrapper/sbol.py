import sbol_swig
import sys
from cStringIO import StringIO

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

def return_stdout(fn):
    def decorated_fn(*args, **kwargs):
        'Capture and return the output stream during a function call'
        backup = sys.stdout
        sys.stdout = StringIO()
        fn(*args, **kwargs)
        output = sys.stdout.getvalue()
        sys.stdout.close()
        sys.stdout = backup
        return output
    return decorated_fn

class DNASequence(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNASequence(uri)

    def __del__(self):
        if sbol_swig.isDNASequence(self.ptr):
            sbol_swig.deleteDNASequence(self.ptr)

    @return_stdout
    def __str__(self):
        sbol_swig.printDNASequence(self.ptr, 0)

    def get_uri(self):
        return sbol_swig.getDNASequenceURI(self.ptr)

class SequenceAnnotation(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createSequenceAnnotation(uri)

    def __del__(self):
        if sbol_swig.isSequenceAnnotation(self.ptr):
            sbol_swig.deleteSequenceAnnotation(self.ptr)

    @return_stdout
    def __str__(self):
        sbol_swig.printSequenceAnnotation(self.ptr, 0)

    def get_uri(self):
        return sbol_swig.getSequenceAnnotationURI(self.ptr)

class DNAComponent(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNAComponent(uri)

    def __del__(self):
        if sbol_swig.isDNAComponent(self.ptr):
            sbol_swig.deleteDNAComponent(self.ptr)
            
    @return_stdout
    def __str__(self):
        sbol_swig.printDNAComponent(self.ptr, 0)

    def get_uri(self):
        return sbol_swig.getDNAComponentURI(self.ptr)

class Collection(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createCollection(uri)

    def __del__(self):
        sbol_swig.deleteCollection(self.ptr)

    @return_stdout
    def __str__(self):
        sbol_swig.printCollection(self.ptr, 0)

    def get_uri(self):
        return sbol_swig.getCollectionURI(self.ptr)

if __name__ == '__main__':
    c1 = Collection('collection1')
    dc1 = DNAComponent('component1')
    ds1 = DNASequence('sequence1')
    print c1
    print dc1
    print ds1

