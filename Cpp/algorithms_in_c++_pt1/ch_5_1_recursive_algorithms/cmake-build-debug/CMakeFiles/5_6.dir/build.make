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
CMAKE_SOURCE_DIR = /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/5_6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5_6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5_6.dir/flags.make

CMakeFiles/5_6.dir/5_6.cpp.o: CMakeFiles/5_6.dir/flags.make
CMakeFiles/5_6.dir/5_6.cpp.o: ../5_6.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/5_6.dir/5_6.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5_6.dir/5_6.cpp.o -c /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/5_6.cpp

CMakeFiles/5_6.dir/5_6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5_6.dir/5_6.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/5_6.cpp > CMakeFiles/5_6.dir/5_6.cpp.i

CMakeFiles/5_6.dir/5_6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5_6.dir/5_6.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/5_6.cpp -o CMakeFiles/5_6.dir/5_6.cpp.s

CMakeFiles/5_6.dir/5_6.cpp.o.requires:

.PHONY : CMakeFiles/5_6.dir/5_6.cpp.o.requires

CMakeFiles/5_6.dir/5_6.cpp.o.provides: CMakeFiles/5_6.dir/5_6.cpp.o.requires
	$(MAKE) -f CMakeFiles/5_6.dir/build.make CMakeFiles/5_6.dir/5_6.cpp.o.provides.build
.PHONY : CMakeFiles/5_6.dir/5_6.cpp.o.provides

CMakeFiles/5_6.dir/5_6.cpp.o.provides.build: CMakeFiles/5_6.dir/5_6.cpp.o


# Object files for target 5_6
5_6_OBJECTS = \
"CMakeFiles/5_6.dir/5_6.cpp.o"

# External object files for target 5_6
5_6_EXTERNAL_OBJECTS =

5_6: CMakeFiles/5_6.dir/5_6.cpp.o
5_6: CMakeFiles/5_6.dir/build.make
5_6: CMakeFiles/5_6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 5_6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5_6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5_6.dir/build: 5_6

.PHONY : CMakeFiles/5_6.dir/build

CMakeFiles/5_6.dir/requires: CMakeFiles/5_6.dir/5_6.cpp.o.requires

.PHONY : CMakeFiles/5_6.dir/requires

CMakeFiles/5_6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5_6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5_6.dir/clean

CMakeFiles/5_6.dir/depend:
	cd /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_5_1_recursive_algorithms/cmake-build-debug/CMakeFiles/5_6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/5_6.dir/depend

