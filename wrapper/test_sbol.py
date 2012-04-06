import unittest
import sbol
import random
import string

URIS_USED = set()
RANDOM_CHARS = string.ascii_letters \
             + string.whitespace \
             + string.punctuation

def random_string(limit=30):
    length = random.randint(0, limit)
    string = ''.join(random.choice(RANDOM_CHARS) for n in range(length))
    return string

def random_uri(limit=30):
    while True:
        uri = random_string()
        global URIS_USED
        if not uri in URIS_USED:
            URIS_USED.add(uri)
            return uri

class TestSBOLObject(unittest.TestCase):
    def assertReadOnly(self, obj, attr):
        try:
            obj.__getattribute__(attr)
            obj.__setattr__(attr, None)
            raise AssertionError
        except AttributeError:
            pass

    def assertReadWrite(self, obj, attr):
        content = random_string()
        self.assertEqual(obj.__getattribute__(attr), None)
        obj.__setattr__(attr, content)
        self.assertEqual(obj.__getattribute__(attr), content)
        obj.__setattr__(attr, None)
        self.assertEqual(obj.__getattribute__(attr), None)

    def setUp(self):
        self.assertEqual(sbol.libsbol.getNumSBOLObjects(), 0)
        self.uris    = []
        self.testees = []
        self.createTestees()
        self.assertEqual(len(self.uris), len(self.testees))
        self.assertEqual(len(self.uris), sbol.libsbol.getNumSBOLObjects())

    def createTestees(self):
        for obj in (sbol.DNASequence,
                    sbol.SequenceAnnotation,
                    sbol.DNAComponent,
                    sbol.Collection):
            uri = random_uri()
            self.uris.append(uri)
            self.testees.append(obj(uri))

    def testURI(self):
        for n in range( len(self.testees) ):
            testee = self.testees[n]
            uri = self.uris[n]
            self.assertEqual(testee.uri, uri)
            self.assertReadOnly(testee, 'uri')

    def tearDown(self):
        self.assertEqual(len(self.uris), len(self.testees))
        self.assertEqual(len(self.uris), sbol.libsbol.getNumSBOLObjects())
        del self.testees
        self.assertEqual(sbol.libsbol.getNumSBOLObjects(), 0)

class TestSBOLCompoundObject(TestSBOLObject):
    def createTestees(self):
        for obj in (sbol.DNAComponent,
                    sbol.Collection):
            uri = random_uri()
            self.uris.append(uri)
            self.testees.append(obj(uri))

    def testDisplayID(self):
        for testee in self.testees:
            self.assertReadWrite(testee, 'display_id')

    def testName(self):
        for testee in self.testees:
            self.assertReadWrite(testee, 'name')

    def testDescription(self):
        for testee in self.testees:
            self.assertReadWrite(testee, 'description')

class TestDNASequence(TestSBOLObject):
    def createTestees(self):
        uri = random_uri()
        self.uris.append(uri)
        self.testees.append( sbol.DNASequence(uri) )

    def testNucleotides(self):
        self.assertReadWrite(self.testees[0], 'nucleotides')

class TestSequenceAnnotation(TestSBOLObject):
    def createTestees(self):
        uri = random_uri()
        self.uris.append(uri)
        self.testees.append( sbol.SequenceAnnotation(uri) )

    def testStart(self):        pass
    def testEnd(self):          pass
    def testStrand(self):       pass
    def testSubcomponent(self): pass
    def testPrecedes(self):     pass

class TestDNAComponent(TestSBOLCompoundObject):
    def createTestees(self):
        uri = random_uri()
        self.uris.append(uri)
        self.testees.append( sbol.DNAComponent(uri) )

    def testSequence(self):    pass
    def testAnnotations(self): pass

class TestCollection(TestSBOLCompoundObject):
    def createTestees(self):
        uri = random_uri()
        self.uris.append(uri)
        self.testees.append( sbol.Collection(uri) )

    def testComponents(self): pass

if __name__ == '__main__':
    unittest.main()

