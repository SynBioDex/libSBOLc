#include "sbol.h"

// To actually run the code you need to #include it
// and call this function. You can also use sbol_run_tests,
// which will write xml files for all the CreateValid* examples.

void CreateValid01() {
	DNAComponent *com = createDNAComponent("http://example.com/dc1");
	setDNAComponentDisplayID(com, "DC1");
}

