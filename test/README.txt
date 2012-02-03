building the validator:
1) install cmake, either from cmake.org or with "apt-get install cmake-gui"
2) run cmake-gui, and in "Where is the source code:" put /path/to/this/folder
3) in "Where to build the binaries:", put /path/to/this/folder/BUILD
4) click "Configure" a couple times, and hopefully all the red will go away. then click "Generate".
5) now you can cd into the BUILD folder and build the validator using "make"

testing the validator:
1) follow the steps above to build the validate executable
2) run "./test_validator.sh"

