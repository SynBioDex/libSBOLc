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
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNASequence(uri)

    def __del__(self):
        deleteDNASequence(self.ptr)

    @return_stdout
    def __str__(self):
        printDNASequence(self.ptr, 0)

    def get_uri(self):
        return getDNASequenceURI(self.ptr)

class SequenceAnnotation(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createSequenceAnnotation(uri)

    def __del__(self):
        deleteSequenceAnnotation(self.ptr)

    @return_stdout
    def __str__(self):
        printSequenceAnnotation(self.ptr, 0)

    def get_uri(self):
        return getSequenceAnnotationURI(self.ptr)

class DNAComponent(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createDNAComponent(uri)

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

class Collection(object):
    def __init__(self, uri):
        object.__init__(self)
        self.ptr = createCollection(uri)

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

if __name__ == '__main__':
    c1  = Collection('collection1')
    dc1 = DNAComponent('component1')
    ds1 = DNASequence('sequence1')
    print c1
    print dc1
    print ds1

