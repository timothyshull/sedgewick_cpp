# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.7743.47/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.7743.47/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/main.c.o   -c /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/main.c

CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/main.c > CMakeFiles/main.dir/main.c.i

CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/main.c -o CMakeFiles/main.dir/main.c.s

CMakeFiles/main.dir/main.c.o.requires:

.PHONY : CMakeFiles/main.dir/main.c.o.requires

CMakeFiles/main.dir/main.c.o.provides: CMakeFiles/main.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.c.o.provides.build
.PHONY : CMakeFiles/main.dir/main.c.o.provides

CMakeFiles/main.dir/main.c.o.provides.build: CMakeFiles/main.dir/main.c.o


CMakeFiles/main.dir/dlist.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/dlist.c.o: ../dlist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/dlist.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/dlist.c.o   -c /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/dlist.c

CMakeFiles/main.dir/dlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/dlist.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/dlist.c > CMakeFiles/main.dir/dlist.c.i

CMakeFiles/main.dir/dlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/dlist.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/dlist.c -o CMakeFiles/main.dir/dlist.c.s

CMakeFiles/main.dir/dlist.c.o.requires:

.PHONY : CMakeFiles/main.dir/dlist.c.o.requires

CMakeFiles/main.dir/dlist.c.o.provides: CMakeFiles/main.dir/dlist.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/dlist.c.o.provides.build
.PHONY : CMakeFiles/main.dir/dlist.c.o.provides

CMakeFiles/main.dir/dlist.c.o.provides.build: CMakeFiles/main.dir/dlist.c.o


CMakeFiles/main.dir/list.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/list.c.o: ../list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/list.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/list.c.o   -c /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/list.c

CMakeFiles/main.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/list.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/list.c > CMakeFiles/main.dir/list.c.i

CMakeFiles/main.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/list.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/list.c -o CMakeFiles/main.dir/list.c.s

CMakeFiles/main.dir/list.c.o.requires:

.PHONY : CMakeFiles/main.dir/list.c.o.requires

CMakeFiles/main.dir/list.c.o.provides: CMakeFiles/main.dir/list.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/list.c.o.provides.build
.PHONY : CMakeFiles/main.dir/list.c.o.provides

CMakeFiles/main.dir/list.c.o.provides.build: CMakeFiles/main.dir/list.c.o


CMakeFiles/main.dir/clist.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/clist.c.o: ../clist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/clist.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/clist.c.o   -c /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/clist.c

CMakeFiles/main.dir/clist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/clist.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/clist.c > CMakeFiles/main.dir/clist.c.i

CMakeFiles/main.dir/clist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/clist.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/clist.c -o CMakeFiles/main.dir/clist.c.s

CMakeFiles/main.dir/clist.c.o.requires:

.PHONY : CMakeFiles/main.dir/clist.c.o.requires

CMakeFiles/main.dir/clist.c.o.provides: CMakeFiles/main.dir/clist.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/clist.c.o.provides.build
.PHONY : CMakeFiles/main.dir/clist.c.o.provides

CMakeFiles/main.dir/clist.c.o.provides.build: CMakeFiles/main.dir/clist.c.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.c.o" \
"CMakeFiles/main.dir/dlist.c.o" \
"CMakeFiles/main.dir/list.c.o" \
"CMakeFiles/main.dir/clist.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.c.o
main: CMakeFiles/main.dir/dlist.c.o
main: CMakeFiles/main.dir/list.c.o
main: CMakeFiles/main.dir/clist.c.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/dlist.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/list.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/clist.c.o.requires

.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug /Users/skull/Programming/Algorithms/C/mastering_algorithms_with_c/ch_5_linked_lists/cmake-build-debug/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

