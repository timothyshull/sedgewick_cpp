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
CMAKE_SOURCE_DIR = /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/list.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/list.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/list.dir/flags.make

CMakeFiles/list.dir/list.cpp.o: CMakeFiles/list.dir/flags.make
CMakeFiles/list.dir/list.cpp.o: ../list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/list.dir/list.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/list.dir/list.cpp.o -c /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/list.cpp

CMakeFiles/list.dir/list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/list.dir/list.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/list.cpp > CMakeFiles/list.dir/list.cpp.i

CMakeFiles/list.dir/list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/list.dir/list.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/list.cpp -o CMakeFiles/list.dir/list.cpp.s

CMakeFiles/list.dir/list.cpp.o.requires:

.PHONY : CMakeFiles/list.dir/list.cpp.o.requires

CMakeFiles/list.dir/list.cpp.o.provides: CMakeFiles/list.dir/list.cpp.o.requires
	$(MAKE) -f CMakeFiles/list.dir/build.make CMakeFiles/list.dir/list.cpp.o.provides.build
.PHONY : CMakeFiles/list.dir/list.cpp.o.provides

CMakeFiles/list.dir/list.cpp.o.provides.build: CMakeFiles/list.dir/list.cpp.o


# Object files for target list
list_OBJECTS = \
"CMakeFiles/list.dir/list.cpp.o"

# External object files for target list
list_EXTERNAL_OBJECTS =

list: CMakeFiles/list.dir/list.cpp.o
list: CMakeFiles/list.dir/build.make
list: CMakeFiles/list.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable list"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/list.dir/build: list

.PHONY : CMakeFiles/list.dir/build

CMakeFiles/list.dir/requires: CMakeFiles/list.dir/list.cpp.o.requires

.PHONY : CMakeFiles/list.dir/requires

CMakeFiles/list.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/list.dir/cmake_clean.cmake
.PHONY : CMakeFiles/list.dir/clean

CMakeFiles/list.dir/depend:
	cd /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_3_5_memory_allocation_for_lists/cmake-build-debug/CMakeFiles/list.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/list.dir/depend

