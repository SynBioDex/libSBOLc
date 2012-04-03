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

def capture(fn):
	'Capture the output stream while running a function, and return it'
	backup = sys.stdout
	sys.stdout = StringIO.StringIO()
	fn(args, kwargs)
	output = sys.stdout.getValue()
	sys.stdout.close()
	sys.stdout = backup
	return output

class DNASequence(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNASequence(uri)
        print self.ptr

    def __del__(self):
        if sbol_swig.isDNASequence(self.ptr):
            sbol_swig.deleteDNASequence(self.ptr)

    def getURI(self):
        return sbol_swig.getDNASequenceURI(self.ptr)

class SequenceAnnotation(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createSequenceAnnotation(uri)
        print self.ptr

    def __del__(self):
        if sbol_swig.isSequenceAnnotation(self.ptr):
            sbol_swig.deleteSequenceAnnotation(self.ptr)

        return sbol_swig.getSequenceAnnotationURI(self.ptr)

class DNAComponent(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createDNAComponent(uri)
        print self.ptr

    def __del__(self):
        if sbol_swig.isDNAComponent(self.ptr):
            sbol_swig.deleteDNAComponent(self.ptr)

    def getURI(self):
        return sbol_swig.getDNAComponentURI(self.ptr)

class Collection(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = sbol_swig.createCollection(uri)
        print self.ptr

    def __del__(self):
        if sbol_swig.isCollection(self.ptr):
            sbol_swig.deleteCollection(self.ptr)

    def getURI(self):
        return sbol_swig.getCollectionURI(self.ptr)

if __name__ == '__main__':
    c1 = Collection('collection1')
    dc1 = DNAComponent('component1')
    ds1 = DNASequence('sequence 1')
    print 'c1:', c1.getURI()
    print 'dc1:', dc1.getURI()
    print 'ds1:', ds1.getURI()

