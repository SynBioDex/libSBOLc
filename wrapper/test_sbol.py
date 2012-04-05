import unittest
import sbol

class TestSBOLObject(unittest.TestCase):
    def setUp(self): pass
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

