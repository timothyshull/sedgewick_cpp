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
CMAKE_SOURCE_DIR = /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ch_4_5_new_adts.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ch_4_5_new_adts.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ch_4_5_new_adts.dir/flags.make

CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o: CMakeFiles/ch_4_5_new_adts.dir/flags.make
CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o -c /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/main.cpp

CMakeFiles/ch_4_5_new_adts.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ch_4_5_new_adts.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/main.cpp > CMakeFiles/ch_4_5_new_adts.dir/main.cpp.i

CMakeFiles/ch_4_5_new_adts.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ch_4_5_new_adts.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/main.cpp -o CMakeFiles/ch_4_5_new_adts.dir/main.cpp.s

CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.requires

CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.provides: CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ch_4_5_new_adts.dir/build.make CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.provides

CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.provides.build: CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o


# Object files for target ch_4_5_new_adts
ch_4_5_new_adts_OBJECTS = \
"CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o"

# External object files for target ch_4_5_new_adts
ch_4_5_new_adts_EXTERNAL_OBJECTS =

ch_4_5_new_adts: CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o
ch_4_5_new_adts: CMakeFiles/ch_4_5_new_adts.dir/build.make
ch_4_5_new_adts: CMakeFiles/ch_4_5_new_adts.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ch_4_5_new_adts"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ch_4_5_new_adts.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ch_4_5_new_adts.dir/build: ch_4_5_new_adts

.PHONY : CMakeFiles/ch_4_5_new_adts.dir/build

CMakeFiles/ch_4_5_new_adts.dir/requires: CMakeFiles/ch_4_5_new_adts.dir/main.cpp.o.requires

.PHONY : CMakeFiles/ch_4_5_new_adts.dir/requires

CMakeFiles/ch_4_5_new_adts.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ch_4_5_new_adts.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ch_4_5_new_adts.dir/clean

CMakeFiles/ch_4_5_new_adts.dir/depend:
	cd /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug /Users/skull/Programming/Algorithms/Cpp/algorithms_in_c++_pt1/ch_4_5_new_adts/cmake-build-debug/CMakeFiles/ch_4_5_new_adts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ch_4_5_new_adts.dir/depend

