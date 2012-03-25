# libSBOLc: SBOL C library

[libSBOLc](https://github.com/SynBioDex/libSBOLc) is a C implementation of the [Synthetic Biology Open Language (SBOL)](http://sbolstandard.org). It uses the XML schema and example files from [libSBOLj](https://github.com/SynBioDex/libSBOLj), but the rest of the code was developed separately. The two libraries should eventually present similar interfaces, except where language conventions differ.

## Building libSBOLc from source

To compile libSBOLc, you will need:

* [git](http://git-scm.com/) for downloading the source code
* [CMake](http://www.cmake.org/cmake/resources/software.html) for generating platform-specific build instructions
* a C compiler, such as [MinGW](http://www.mingw.org/wiki/InstallationHOWTOforMinGW) or [gcc](http://gcc.gnu.org/)

First, download them from the links above. Or if you're on Debian/Ubuntu this command should do it:

    sudo apt-get install git cmake-gui build-essential

Then, clone the repository:

    git clone git://github.com/SynBioDex/libSBOLc.git

This will create a <code>libSBOLc</code> directory with the code. Next, run CMake. For "Where is the source code" enter the path to your <code>libSBOLc/source</code> folder. "Where to build the binaries" is up to you and can theoretically be anything, but I've only tested it with <code>libSBOLc/build</code>.

## Testing libSBOLc

## Using libSBOLc
