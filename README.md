# libSBOLc: SBOL C library

[libSBOLc](https://github.com/SynBioDex/libSBOLc) is a C implementation of the [Synthetic Biology Open Language (SBOL)](http://sbolstandard.org). It uses the XML schema and example files from [libSBOLj](https://github.com/SynBioDex/libSBOLj), but the rest of the code was developed separately. The two libraries should eventually present similar interfaces, except where language conventions differ.

## Building libSBOLc from source

To compile libSBOLc, you will need:

* [git](http://git-scm.com/) for downloading the source code
* [CMake](http://www.cmake.org/cmake/resources/software.html) for generating platform-specific build instructions
* a C compiler, such as [MinGW](http://www.mingw.org/wiki/InstallationHOWTOforMinGW) or [gcc](http://gcc.gnu.org/)

First, download them from the links above. Or if you're on Debian/Ubuntu this command should work too:

    sudo apt-get install git cmake-gui build-essential

Then, clone the repository:

    git clone git://github.com/SynBioDex/libSBOLc.git

This will create a <code>libSBOLc</code> directory with the code. Next, run CMake. For "Where is the source code" enter the path to your <code>libSBOLc/source</code> folder. "Where to build the binaries" should be <code>libSBOLc/build</code>.

Click <code>Configure</code>, and choose what type of compiler you want to generate instructions for. All the development has been done using "default native compilers" and MinGW or Unix makefiles, but CMake should also be able to generate projects for Eclipse, Visual Studio, XCode, etc. However, that will probably involve adjusting some paths.

The first time you click <code>Configure</code>, CMake will list variables, like <code>CMAKE_BUILD_TYPE</code> and <code>LIBXML2_INCLUDE_DIR</code>, in red. That means they've been updated. You can probably just click <code>Configure</code> again to make sure everything is set. You can also change variables here. The only SBOL-specific option to be aware of is that setting <code>CMAKE_BUILD_TYPE</code> to "Debug" will also cause libSBOLc to be compiled with some extra debugging statements. After changing varibables you should click <code>Configure</code> again. Once everything is set, click <code>Generate</code> to create the compiler instructions.

The last step is to <code>cd</code> into the <code>libSBOLc/build</code> folder and run the compiler.

For MingGW:

    mingw32-make.exe

For gcc:

    make

Binaries will be generated in the <code>libSBOLc/release</code> folder.

## Testing libSBOLc

## Using libSBOLc
