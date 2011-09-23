=====================
   HOW TO BUILD
=====================

Assuming that you already have the source code for libSBOLc (since you are reading this file)
Lets say that the source code is located in the libSBOLc folder

1) Install Cmake from cmake.org
2) Run cmake-gui
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

