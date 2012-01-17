=====================
      ABOUT
=====================
This library reads RDF files and creates C data structures from 
the triplets. The Raptor2 library, which is a subset of the Redland
RDF library, is used to parse the RDF files. 

The API itself is C, but the library is written in C++, primarily because
of the use of std::map, which is used to create a look-up table for
all items read from a file.

See parser.h for all the available functions and data structures.

=====================
 GETTING THE CODE
=====================
Getting the code: 
1) Install Git
2) Use the following command to get the libSBOLc source:
    git clone https://github.com/SynBioDex/libSBOLc.git

If you are using Windows, the git command might require the full path, i.e. C:\Program Files\Git\git.exe

=====================
   HOW TO BUILD
=====================

Lets say that the liBSBOLc source code is located in a folder called "libSBOLc"

1) Install Cmake from cmake.org
    for Linux, just type 'apt-get cmake cmake-gui'

2) Run cmake-gui
    In the Cmake program, find two text boxes labeled, "where is the source code" and "where to build"

3) Type the full libSBOLc/ folder path for the line that says "where is the source code"

4) Type libSBOLc/BUILD folder path for the line that says "where to build"

5) Click the "Configure" button

6) Cmake will create the BUILD folder and then ask you to select the compiler. 
    It is recommended that you use standard compilers, e.g. gcc for Unix and 
    Visual Studio or MinGW for MS Windows.

7) Once configuration is done, click the "Generate" button

8) Go to the libSBOLc/BUILD folder. 
    If you used Visual Studio as the compiler, you will find a project file (.sln) -- open it and build all
    If you used GCC, you will find a makefile. cd into this folder and run "make"

=====================
   HOW TO TEST
=====================

Once you've created the sboltest binary, you can use it to read
an RDF file and display the resulting SBOL data structures.

1) Move files
    Copy the file "example.nt" from libSBOLc/ to libSBOLc/BUILD.
    Alternatively, create a new directory libSBOLc/DIST and put both sboltest and example.nt in it.

2) Run the test:
    cd into the DIST directory if needed.
    ./sboltest

It should print the following:

component id = component1
      num. collections = 1
         collection = collectionA
      num. annotations = 3
         subComponent component2
            precedes sa3
            precedes sa3
         subComponent component3
         subComponent component3

component id = component2
      num. collections = 1
         collection = collectionB
      num. annotations = 1
         subComponent component4

component id = component3
      num. collections = 1
         collection = collectionB
      num. annotations = 0

component id = component4
      num. collections = 1
         collection = collectionB
      num. annotations = 0

=====================
   TO DO
=====================
- function to write-out the data structures in RDF
- SWIG wrapper for Python
- additional tests

