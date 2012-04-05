import unittest
import sbol
import random
import string

URIS_USED = set()

def random_uri(length=20):
    options = string.ascii_uppercase + string.ascii_lowercase
    while True:
        uri = ''.join(random.choice(options) for n in range(length))
        global URIS_USED
        if not uri in URIS_USED:
            URIS_USED.add(uri)
            return uri

class TestSBOLObject(unittest.TestCase):
    def setUp(self):
        self.assertEqual(sbol.sbol_swig.getNumSBOLObjects(), 0)
        self.uris = set()
        self.testees = set()
        self.testees.add( sbol.DNASequence(random_uri())        )
        self.testees.add( sbol.SequenceAnnotation(random_uri()) )
        self.testees.add( sbol.DNAComponent(random_uri())       )
        self.testees.add( sbol.Collection(random_uri())         )

    def tearDown(self):
        sbol.sbol_swig.cleanupSBOLCore()
        self.assertEqual(sbol.sbol_swig.getNumSBOLObjects(), 0)

    def testInit(self): pass
    def testDel(self): pass
    def testStr(self): pass
    def testURI(self): pass

class TestSBOLCompoundObject(unittest.TestCase):
    def testDisplayID(self): pass
    def testName(self): pass
    def testDescription(self): pass

class TestDNASequence(unittest.TestCase):
    def testNucleotides(self): pass

class TestSequenceAnnotation(unittest.TestCase):
    def testStart(self): pass
    def testEnd(self): pass
    def testStrand(self): pass
    def testSubcomponent(self): pass
    def testPrecedes(self): pass

class TestDNAComponent(unittest.TestCase):
    def testSequence(self): pass
    def testAnnotations(self): pass

class TestCollection(unittest.TestCase):
    def testComponents(self): pass

if __name__ == '__main__':
    unittest.main()

