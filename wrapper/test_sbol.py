import unittest
import sbol
import random
import string

URIS_USED = set()
URI_CHARS = string.ascii_letters \
          + string.whitespace \
          + string.punctuation

def random_uri(limit=30):
    while True:
        length = random.randint(0, limit)
        uri = ''.join(random.choice(URI_CHARS) for n in range(length))
        global URIS_USED
        if not uri in URIS_USED:
            URIS_USED.add(uri)
            return uri

class TestSBOLObject(unittest.TestCase):
    def setUp(self):
        self.assertEqual(sbol.libsbol.getNumSBOLObjects(), 0)
        self.uris    = []
        self.testees = []
        for obj in (sbol.DNASequence,
                    sbol.SequenceAnnotation,
                    sbol.DNAComponent,
                    sbol.Collection):
            uri = random_uri()
            self.uris.append(uri)
            self.testees.append(obj(uri))
        self.assertEqual(len(self.uris), len(self.testees))
        self.assertEqual(len(self.uris), sbol.libsbol.getNumSBOLObjects())

    def assertReadOnly(self, obj, attr):
        "Make sure an attribute can't be written"
        try:
            obj.__setattr__(attr, None)
            raise AssertionError # todo better error
        except AttributeError:
            pass

    def testURI(self):
        for n in range( len(self.testees) ):
            self.assertEqual(self.testees[n].uri, self.uris[n])
            self.assertReadOnly(self.testees[n], 'uri')

    def tearDown(self):
        self.assertEqual(len(self.uris), len(self.testees))
        self.assertEqual(len(self.uris), sbol.libsbol.getNumSBOLObjects())
        # will this free them immediately?
        del self.testees
        self.assertEqual(sbol.libsbol.getNumSBOLObjects(), 0)

class TestSBOLCompoundObject(unittest.TestCase):
    def setUp(self): pass
    def tearDown(self): pass
    def testDisplayID(self): pass
    def testName(self): pass
    def testDescription(self): pass

class TestDNASequence(unittest.TestCase):
    def setUp(self): pass
    def tearDown(self): pass
    def testNucleotides(self): pass

class TestSequenceAnnotation(unittest.TestCase):
    def setUp(self): pass
    def tearDown(self): pass
    def testStart(self): pass
    def testEnd(self): pass
    def testStrand(self): pass
    def testSubcomponent(self): pass
    def testPrecedes(self): pass

class TestDNAComponent(unittest.TestCase):
    def setUp(self): pass
    def tearDown(self): pass
    def testSequence(self): pass
    def testAnnotations(self): pass

class TestCollection(unittest.TestCase):
    def setUp(self): pass
    def tearDown(self): pass
    def testComponents(self): pass

if __name__ == '__main__':
    unittest.main()

