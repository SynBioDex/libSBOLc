libSBOLc: SBOL C library
========================

[libSBOLc](https://github.com/SynBioDex/libSBOLc) is a C library for working with the [Synthetic Biology Open Language (SBOL)](http://sbolstandard.org). It uses the XML schema and example files from [libSBOLj](https://github.com/SynBioDex/libSBOLj), but the rest of the code was developed separately. The two libraries should eventually present similar interfaces, except where language conventions differ.

The rest of this file is a quick guide to getting started with common tasks. For more detailed information, see:

* [the online documentation](http://synbiodex.github.com/libSBOLc)
* [some example code](https://github.com/SynBioDex/libSBOLc/tree/master/examples)

Building from source
--------------------

To compile libSBOLc, you will need:

* [git](http://git-scm.com/) for downloading the source code
* [CMake](http://www.cmake.org/cmake/resources/software.html) for generating platform-specific build instructions
* a C compiler, such as [gcc](http://gcc.gnu.org/) or [MinGW](http://www.mingw.org/wiki/InstallationHOWTOforMinGW)

First, download them from the links above. Or if you're on Debian/Ubuntu this command should work:

    sudo apt-get install git cmake-gui build-essential

If you want to update the documentation you also need [Doxygen](http://www.stack.nl/~dimitri/doxygen/), and to generate the Python wrapper you need [SWIG](http://www.swig.org/). To install them on Debian/Ubuntu:

    sudo apt-get install doxygen swig

Then, clone the repository:

    git clone git://github.com/SynBioDex/libSBOLc.git

This will create a <code>libSBOLc</code> directory with the code. Next, run CMake. For "Where is the source code" enter the path to your <code>libSBOLc</code> folder. "Where to build the binaries" can technically be anywhere, but it's only been tested with <code>libSBOLc/build</code>.

Click <code>Configure</code>, and choose what type of compiler you want to generate instructions for. All the development has been done using "default native compilers" and MinGW on Windows or Unix makefiles on Mac/Linux. CMake should also be able to generate projects for Eclipse, Visual Studio, XCode, etc. However, that will probably involve adjusting some paths.

The first time you click <code>Configure</code>, CMake will list variables, like <code>CMAKE_BUILD_TYPE</code> and <code>LIBXML2_INCLUDE_DIR</code>, in red. That means they've been updated. To build the main SBOL library, just click <code>Configure</code> again until the red goes away to make sure everything is set. This is also where you set up the optional targets: examples, tests, manual, and wrapper. To add them check the appropriate boxes (SBOL_BUILD_EXAMPLES, for example) and then <code>Configure</code> again to adjust the settings. The other SBOL-specific option to be aware of is that setting <code>CMAKE_BUILD_TYPE</code> to "Debug" will cause libSBOLc to be compiled with some extra debugging statements. Once everything is set, click <code>Generate</code> to create the compiler instructions.

The last step is to <code>cd</code> into the <code>libSBOLc/build</code> folder and run the compiler.

    make

or

    mingw32-make.exe

Binaries will be generated in the <code>libSBOLc/release</code> folder. If you added optional targets there may be several versions of libsbol in there; you
want the one named just <code>libsbol.so</code>, <code>libsbol.dll</code>, or <code>libsbol.dylib</code>.

Testing
-------

Once you've configured and built libSBOLc, you can <code>cd</code> into the <code>libSBOLc/release</code> folder and run some simple tests to check that everything works:

    ./sbol_run_tests

or 

    ./sbol_run_tests.exe

Incorporating libSBOLc into your code
-------------------------------------

To use libsbol in your own code, <code>#include "sbol.h"</code>. Then there are only a few important functions you need to know to get started reading, writing, and manipulating SBOL files:

* readSBOLCore imports SBOL objects from a file, and writeSBOLCore serializes them again.

* isValidSBOL checks that an xmlDoc conforms to the SBOL schema. Using it involves parsing with libxml. There's an example of that in
  <code>libSBOLc/examples/code/sbol_validate.c</code>, but it shouldn't be necessary in most cases since readSBOLCore and writeSBOLCore
  both call it internally.

* There are constructors, destructors, getters, and setters for each type of SBOL object.
  For the most part they follow a pretty obvious formula:
  setDNAComponentDisplayID and getDNAComponentDisplayID, for example. But there are also some non-obvious ones, like 
  addPrecedesRelationship. For those the [index of all available functions](http://synbiodex.github.com/libSBOLc/globals.html)
  is a good place to look.
  There's also code to create each of the xml example files in <code>libSBOLc/examples/code</code>.

* cleanupSBOLCore frees all the SBOL objects from memory.

Updating the documentation
--------------------------

Updating the Python wrapper
---------------------------
