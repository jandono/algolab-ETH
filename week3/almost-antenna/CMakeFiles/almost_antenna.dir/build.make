# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna"

# Include any dependencies generated for this target.
include CMakeFiles/almost_antenna.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/almost_antenna.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/almost_antenna.dir/flags.make

CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o: CMakeFiles/almost_antenna.dir/flags.make
CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o: almost_antenna.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o -c "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna/almost_antenna.cpp"

CMakeFiles/almost_antenna.dir/almost_antenna.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/almost_antenna.dir/almost_antenna.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna/almost_antenna.cpp" > CMakeFiles/almost_antenna.dir/almost_antenna.cpp.i

CMakeFiles/almost_antenna.dir/almost_antenna.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/almost_antenna.dir/almost_antenna.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna/almost_antenna.cpp" -o CMakeFiles/almost_antenna.dir/almost_antenna.cpp.s

CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.requires:

.PHONY : CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.requires

CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.provides: CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.requires
	$(MAKE) -f CMakeFiles/almost_antenna.dir/build.make CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.provides.build
.PHONY : CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.provides

CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.provides.build: CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o


# Object files for target almost_antenna
almost_antenna_OBJECTS = \
"CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o"

# External object files for target almost_antenna
almost_antenna_EXTERNAL_OBJECTS =

almost_antenna: CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o
almost_antenna: CMakeFiles/almost_antenna.dir/build.make
almost_antenna: /usr/local/lib/libmpfr.dylib
almost_antenna: /usr/local/lib/libgmp.dylib
almost_antenna: /usr/local/lib/libCGAL_Core.13.0.1.dylib
almost_antenna: /usr/local/lib/libCGAL.13.0.1.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: /usr/local/lib/libCGAL_Core.13.0.1.dylib
almost_antenna: /usr/local/lib/libCGAL.13.0.1.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: /usr/local/lib/libCGAL_Core.13.0.1.dylib
almost_antenna: /usr/local/lib/libCGAL.13.0.1.dylib
almost_antenna: /usr/local/lib/libCGAL_Core.13.0.1.dylib
almost_antenna: /usr/local/lib/libCGAL.13.0.1.dylib
almost_antenna: /usr/local/lib/libboost_thread-mt.dylib
almost_antenna: /usr/local/lib/libboost_system-mt.dylib
almost_antenna: /usr/local/lib/libboost_chrono-mt.dylib
almost_antenna: /usr/local/lib/libboost_date_time-mt.dylib
almost_antenna: /usr/local/lib/libboost_atomic-mt.dylib
almost_antenna: CMakeFiles/almost_antenna.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable almost_antenna"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/almost_antenna.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/almost_antenna.dir/build: almost_antenna

.PHONY : CMakeFiles/almost_antenna.dir/build

CMakeFiles/almost_antenna.dir/requires: CMakeFiles/almost_antenna.dir/almost_antenna.cpp.o.requires

.PHONY : CMakeFiles/almost_antenna.dir/requires

CMakeFiles/almost_antenna.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/almost_antenna.dir/cmake_clean.cmake
.PHONY : CMakeFiles/almost_antenna.dir/clean

CMakeFiles/almost_antenna.dir/depend:
	cd "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna" "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna" "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna" "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna" "/Users/ac1d/Programming/Sublime-Workspace/Algo Lab/week3/almost-antenna/CMakeFiles/almost_antenna.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/almost_antenna.dir/depend

