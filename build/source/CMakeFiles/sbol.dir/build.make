# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\user\Dev\libSBOLc_v1\libSBOLc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build

# Include any dependencies generated for this target.
include source/CMakeFiles/sbol.dir/depend.make

# Include the progress variables for this target.
include source/CMakeFiles/sbol.dir/progress.make

# Include the compile flags for this target's objects.
include source/CMakeFiles/sbol.dir/flags.make

source/CMakeFiles/sbol.dir/array.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/array.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/array.c.obj: ../source/array.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/array.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\array.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\array.c

source/CMakeFiles/sbol.dir/array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/array.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\array.c > CMakeFiles\sbol.dir\array.c.i

source/CMakeFiles/sbol.dir/array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/array.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\array.c -o CMakeFiles\sbol.dir\array.c.s

source/CMakeFiles/sbol.dir/array.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/array.c.obj.requires

source/CMakeFiles/sbol.dir/array.c.obj.provides: source/CMakeFiles/sbol.dir/array.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/array.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/array.c.obj.provides

source/CMakeFiles/sbol.dir/array.c.obj.provides.build: source/CMakeFiles/sbol.dir/array.c.obj

source/CMakeFiles/sbol.dir/collection.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/collection.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/collection.c.obj: ../source/collection.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/collection.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\collection.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\collection.c

source/CMakeFiles/sbol.dir/collection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/collection.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\collection.c > CMakeFiles\sbol.dir\collection.c.i

source/CMakeFiles/sbol.dir/collection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/collection.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\collection.c -o CMakeFiles\sbol.dir\collection.c.s

source/CMakeFiles/sbol.dir/collection.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/collection.c.obj.requires

source/CMakeFiles/sbol.dir/collection.c.obj.provides: source/CMakeFiles/sbol.dir/collection.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/collection.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/collection.c.obj.provides

source/CMakeFiles/sbol.dir/collection.c.obj.provides.build: source/CMakeFiles/sbol.dir/collection.c.obj

source/CMakeFiles/sbol.dir/dnacomponent.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/dnacomponent.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/dnacomponent.c.obj: ../source/dnacomponent.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/dnacomponent.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\dnacomponent.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\dnacomponent.c

source/CMakeFiles/sbol.dir/dnacomponent.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/dnacomponent.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\dnacomponent.c > CMakeFiles\sbol.dir\dnacomponent.c.i

source/CMakeFiles/sbol.dir/dnacomponent.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/dnacomponent.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\dnacomponent.c -o CMakeFiles\sbol.dir\dnacomponent.c.s

source/CMakeFiles/sbol.dir/dnacomponent.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/dnacomponent.c.obj.requires

source/CMakeFiles/sbol.dir/dnacomponent.c.obj.provides: source/CMakeFiles/sbol.dir/dnacomponent.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/dnacomponent.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/dnacomponent.c.obj.provides

source/CMakeFiles/sbol.dir/dnacomponent.c.obj.provides.build: source/CMakeFiles/sbol.dir/dnacomponent.c.obj

source/CMakeFiles/sbol.dir/dnasequence.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/dnasequence.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/dnasequence.c.obj: ../source/dnasequence.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/dnasequence.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\dnasequence.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\dnasequence.c

source/CMakeFiles/sbol.dir/dnasequence.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/dnasequence.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\dnasequence.c > CMakeFiles\sbol.dir\dnasequence.c.i

source/CMakeFiles/sbol.dir/dnasequence.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/dnasequence.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\dnasequence.c -o CMakeFiles\sbol.dir\dnasequence.c.s

source/CMakeFiles/sbol.dir/dnasequence.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/dnasequence.c.obj.requires

source/CMakeFiles/sbol.dir/dnasequence.c.obj.provides: source/CMakeFiles/sbol.dir/dnasequence.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/dnasequence.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/dnasequence.c.obj.provides

source/CMakeFiles/sbol.dir/dnasequence.c.obj.provides.build: source/CMakeFiles/sbol.dir/dnasequence.c.obj

source/CMakeFiles/sbol.dir/document.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/document.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/document.c.obj: ../source/document.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/document.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\document.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\document.c

source/CMakeFiles/sbol.dir/document.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/document.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\document.c > CMakeFiles\sbol.dir\document.c.i

source/CMakeFiles/sbol.dir/document.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/document.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\document.c -o CMakeFiles\sbol.dir\document.c.s

source/CMakeFiles/sbol.dir/document.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/document.c.obj.requires

source/CMakeFiles/sbol.dir/document.c.obj.provides: source/CMakeFiles/sbol.dir/document.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/document.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/document.c.obj.provides

source/CMakeFiles/sbol.dir/document.c.obj.provides.build: source/CMakeFiles/sbol.dir/document.c.obj

source/CMakeFiles/sbol.dir/object.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/object.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/object.c.obj: ../source/object.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/object.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\object.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\object.c

source/CMakeFiles/sbol.dir/object.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/object.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\object.c > CMakeFiles\sbol.dir\object.c.i

source/CMakeFiles/sbol.dir/object.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/object.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\object.c -o CMakeFiles\sbol.dir\object.c.s

source/CMakeFiles/sbol.dir/object.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/object.c.obj.requires

source/CMakeFiles/sbol.dir/object.c.obj.provides: source/CMakeFiles/sbol.dir/object.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/object.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/object.c.obj.provides

source/CMakeFiles/sbol.dir/object.c.obj.provides.build: source/CMakeFiles/sbol.dir/object.c.obj

source/CMakeFiles/sbol.dir/property.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/property.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/property.c.obj: ../source/property.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/property.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\property.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\property.c

source/CMakeFiles/sbol.dir/property.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/property.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\property.c > CMakeFiles\sbol.dir\property.c.i

source/CMakeFiles/sbol.dir/property.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/property.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\property.c -o CMakeFiles\sbol.dir\property.c.s

source/CMakeFiles/sbol.dir/property.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/property.c.obj.requires

source/CMakeFiles/sbol.dir/property.c.obj.provides: source/CMakeFiles/sbol.dir/property.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/property.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/property.c.obj.provides

source/CMakeFiles/sbol.dir/property.c.obj.provides.build: source/CMakeFiles/sbol.dir/property.c.obj

source/CMakeFiles/sbol.dir/reader.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/reader.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/reader.c.obj: ../source/reader.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/reader.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\reader.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\reader.c

source/CMakeFiles/sbol.dir/reader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/reader.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\reader.c > CMakeFiles\sbol.dir\reader.c.i

source/CMakeFiles/sbol.dir/reader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/reader.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\reader.c -o CMakeFiles\sbol.dir\reader.c.s

source/CMakeFiles/sbol.dir/reader.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/reader.c.obj.requires

source/CMakeFiles/sbol.dir/reader.c.obj.provides: source/CMakeFiles/sbol.dir/reader.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/reader.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/reader.c.obj.provides

source/CMakeFiles/sbol.dir/reader.c.obj.provides.build: source/CMakeFiles/sbol.dir/reader.c.obj

source/CMakeFiles/sbol.dir/sequenceannotation.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/sequenceannotation.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/sequenceannotation.c.obj: ../source/sequenceannotation.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/sequenceannotation.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\sequenceannotation.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\sequenceannotation.c

source/CMakeFiles/sbol.dir/sequenceannotation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/sequenceannotation.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\sequenceannotation.c > CMakeFiles\sbol.dir\sequenceannotation.c.i

source/CMakeFiles/sbol.dir/sequenceannotation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/sequenceannotation.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\sequenceannotation.c -o CMakeFiles\sbol.dir\sequenceannotation.c.s

source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.requires

source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.provides: source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.provides

source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.provides.build: source/CMakeFiles/sbol.dir/sequenceannotation.c.obj

source/CMakeFiles/sbol.dir/utilities.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/utilities.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/utilities.c.obj: ../source/utilities.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/utilities.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\utilities.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\utilities.c

source/CMakeFiles/sbol.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/utilities.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\utilities.c > CMakeFiles\sbol.dir\utilities.c.i

source/CMakeFiles/sbol.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/utilities.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\utilities.c -o CMakeFiles\sbol.dir\utilities.c.s

source/CMakeFiles/sbol.dir/utilities.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/utilities.c.obj.requires

source/CMakeFiles/sbol.dir/utilities.c.obj.provides: source/CMakeFiles/sbol.dir/utilities.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/utilities.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/utilities.c.obj.provides

source/CMakeFiles/sbol.dir/utilities.c.obj.provides.build: source/CMakeFiles/sbol.dir/utilities.c.obj

source/CMakeFiles/sbol.dir/validator.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/validator.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/validator.c.obj: ../source/validator.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/validator.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\validator.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\validator.c

source/CMakeFiles/sbol.dir/validator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/validator.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\validator.c > CMakeFiles\sbol.dir\validator.c.i

source/CMakeFiles/sbol.dir/validator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/validator.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\validator.c -o CMakeFiles\sbol.dir\validator.c.s

source/CMakeFiles/sbol.dir/validator.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/validator.c.obj.requires

source/CMakeFiles/sbol.dir/validator.c.obj.provides: source/CMakeFiles/sbol.dir/validator.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/validator.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/validator.c.obj.provides

source/CMakeFiles/sbol.dir/validator.c.obj.provides.build: source/CMakeFiles/sbol.dir/validator.c.obj

source/CMakeFiles/sbol.dir/writer.c.obj: source/CMakeFiles/sbol.dir/flags.make
source/CMakeFiles/sbol.dir/writer.c.obj: source/CMakeFiles/sbol.dir/includes_C.rsp
source/CMakeFiles/sbol.dir/writer.c.obj: ../source/writer.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/CMakeFiles/sbol.dir/writer.c.obj"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\sbol.dir\writer.c.obj   -c C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\writer.c

source/CMakeFiles/sbol.dir/writer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sbol.dir/writer.c.i"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\writer.c > CMakeFiles\sbol.dir\writer.c.i

source/CMakeFiles/sbol.dir/writer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sbol.dir/writer.c.s"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && c:\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source\writer.c -o CMakeFiles\sbol.dir\writer.c.s

source/CMakeFiles/sbol.dir/writer.c.obj.requires:
.PHONY : source/CMakeFiles/sbol.dir/writer.c.obj.requires

source/CMakeFiles/sbol.dir/writer.c.obj.provides: source/CMakeFiles/sbol.dir/writer.c.obj.requires
	$(MAKE) -f source\CMakeFiles\sbol.dir\build.make source/CMakeFiles/sbol.dir/writer.c.obj.provides.build
.PHONY : source/CMakeFiles/sbol.dir/writer.c.obj.provides

source/CMakeFiles/sbol.dir/writer.c.obj.provides.build: source/CMakeFiles/sbol.dir/writer.c.obj

# Object files for target sbol
sbol_OBJECTS = \
"CMakeFiles/sbol.dir/array.c.obj" \
"CMakeFiles/sbol.dir/collection.c.obj" \
"CMakeFiles/sbol.dir/dnacomponent.c.obj" \
"CMakeFiles/sbol.dir/dnasequence.c.obj" \
"CMakeFiles/sbol.dir/document.c.obj" \
"CMakeFiles/sbol.dir/object.c.obj" \
"CMakeFiles/sbol.dir/property.c.obj" \
"CMakeFiles/sbol.dir/reader.c.obj" \
"CMakeFiles/sbol.dir/sequenceannotation.c.obj" \
"CMakeFiles/sbol.dir/utilities.c.obj" \
"CMakeFiles/sbol.dir/validator.c.obj" \
"CMakeFiles/sbol.dir/writer.c.obj"

# External object files for target sbol
sbol_EXTERNAL_OBJECTS =

../release/library/libsbol.a: source/CMakeFiles/sbol.dir/array.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/collection.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/dnacomponent.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/dnasequence.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/document.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/object.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/property.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/reader.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/sequenceannotation.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/utilities.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/validator.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/writer.c.obj
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/build.make
../release/library/libsbol.a: source/CMakeFiles/sbol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library ..\..\release\library\libsbol.a"
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && $(CMAKE_COMMAND) -P CMakeFiles\sbol.dir\cmake_clean_target.cmake
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sbol.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/CMakeFiles/sbol.dir/build: ../release/library/libsbol.a
.PHONY : source/CMakeFiles/sbol.dir/build

source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/array.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/collection.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/dnacomponent.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/dnasequence.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/document.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/object.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/property.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/reader.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/sequenceannotation.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/utilities.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/validator.c.obj.requires
source/CMakeFiles/sbol.dir/requires: source/CMakeFiles/sbol.dir/writer.c.obj.requires
.PHONY : source/CMakeFiles/sbol.dir/requires

source/CMakeFiles/sbol.dir/clean:
	cd /d C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source && $(CMAKE_COMMAND) -P CMakeFiles\sbol.dir\cmake_clean.cmake
.PHONY : source/CMakeFiles/sbol.dir/clean

source/CMakeFiles/sbol.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\user\Dev\libSBOLc_v1\libSBOLc C:\Users\user\Dev\libSBOLc_v1\libSBOLc\source C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source C:\Users\user\Dev\libSBOLc_v1\libSBOLc\build\source\CMakeFiles\sbol.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : source/CMakeFiles/sbol.dir/depend

