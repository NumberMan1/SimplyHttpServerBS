# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/number/SimplyHttpServerBS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/number/SimplyHttpServerBS/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mysrc.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mysrc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mysrc.dir/flags.make

src/CMakeFiles/mysrc.dir/Log.cpp.o: src/CMakeFiles/mysrc.dir/flags.make
src/CMakeFiles/mysrc.dir/Log.cpp.o: ../src/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/number/SimplyHttpServerBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mysrc.dir/Log.cpp.o"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysrc.dir/Log.cpp.o -c /home/number/SimplyHttpServerBS/src/Log.cpp

src/CMakeFiles/mysrc.dir/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysrc.dir/Log.cpp.i"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/number/SimplyHttpServerBS/src/Log.cpp > CMakeFiles/mysrc.dir/Log.cpp.i

src/CMakeFiles/mysrc.dir/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysrc.dir/Log.cpp.s"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/number/SimplyHttpServerBS/src/Log.cpp -o CMakeFiles/mysrc.dir/Log.cpp.s

src/CMakeFiles/mysrc.dir/MLibEvent.cpp.o: src/CMakeFiles/mysrc.dir/flags.make
src/CMakeFiles/mysrc.dir/MLibEvent.cpp.o: ../src/MLibEvent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/number/SimplyHttpServerBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mysrc.dir/MLibEvent.cpp.o"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysrc.dir/MLibEvent.cpp.o -c /home/number/SimplyHttpServerBS/src/MLibEvent.cpp

src/CMakeFiles/mysrc.dir/MLibEvent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysrc.dir/MLibEvent.cpp.i"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/number/SimplyHttpServerBS/src/MLibEvent.cpp > CMakeFiles/mysrc.dir/MLibEvent.cpp.i

src/CMakeFiles/mysrc.dir/MLibEvent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysrc.dir/MLibEvent.cpp.s"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/number/SimplyHttpServerBS/src/MLibEvent.cpp -o CMakeFiles/mysrc.dir/MLibEvent.cpp.s

src/CMakeFiles/mysrc.dir/Pub.cpp.o: src/CMakeFiles/mysrc.dir/flags.make
src/CMakeFiles/mysrc.dir/Pub.cpp.o: ../src/Pub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/number/SimplyHttpServerBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/mysrc.dir/Pub.cpp.o"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysrc.dir/Pub.cpp.o -c /home/number/SimplyHttpServerBS/src/Pub.cpp

src/CMakeFiles/mysrc.dir/Pub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysrc.dir/Pub.cpp.i"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/number/SimplyHttpServerBS/src/Pub.cpp > CMakeFiles/mysrc.dir/Pub.cpp.i

src/CMakeFiles/mysrc.dir/Pub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysrc.dir/Pub.cpp.s"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/number/SimplyHttpServerBS/src/Pub.cpp -o CMakeFiles/mysrc.dir/Pub.cpp.s

src/CMakeFiles/mysrc.dir/WebOp.cpp.o: src/CMakeFiles/mysrc.dir/flags.make
src/CMakeFiles/mysrc.dir/WebOp.cpp.o: ../src/WebOp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/number/SimplyHttpServerBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/mysrc.dir/WebOp.cpp.o"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mysrc.dir/WebOp.cpp.o -c /home/number/SimplyHttpServerBS/src/WebOp.cpp

src/CMakeFiles/mysrc.dir/WebOp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysrc.dir/WebOp.cpp.i"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/number/SimplyHttpServerBS/src/WebOp.cpp > CMakeFiles/mysrc.dir/WebOp.cpp.i

src/CMakeFiles/mysrc.dir/WebOp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysrc.dir/WebOp.cpp.s"
	cd /home/number/SimplyHttpServerBS/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/number/SimplyHttpServerBS/src/WebOp.cpp -o CMakeFiles/mysrc.dir/WebOp.cpp.s

# Object files for target mysrc
mysrc_OBJECTS = \
"CMakeFiles/mysrc.dir/Log.cpp.o" \
"CMakeFiles/mysrc.dir/MLibEvent.cpp.o" \
"CMakeFiles/mysrc.dir/Pub.cpp.o" \
"CMakeFiles/mysrc.dir/WebOp.cpp.o"

# External object files for target mysrc
mysrc_EXTERNAL_OBJECTS =

../lib/libmysrc.a: src/CMakeFiles/mysrc.dir/Log.cpp.o
../lib/libmysrc.a: src/CMakeFiles/mysrc.dir/MLibEvent.cpp.o
../lib/libmysrc.a: src/CMakeFiles/mysrc.dir/Pub.cpp.o
../lib/libmysrc.a: src/CMakeFiles/mysrc.dir/WebOp.cpp.o
../lib/libmysrc.a: src/CMakeFiles/mysrc.dir/build.make
../lib/libmysrc.a: src/CMakeFiles/mysrc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/number/SimplyHttpServerBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../../lib/libmysrc.a"
	cd /home/number/SimplyHttpServerBS/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mysrc.dir/cmake_clean_target.cmake
	cd /home/number/SimplyHttpServerBS/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysrc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mysrc.dir/build: ../lib/libmysrc.a

.PHONY : src/CMakeFiles/mysrc.dir/build

src/CMakeFiles/mysrc.dir/clean:
	cd /home/number/SimplyHttpServerBS/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mysrc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mysrc.dir/clean

src/CMakeFiles/mysrc.dir/depend:
	cd /home/number/SimplyHttpServerBS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/number/SimplyHttpServerBS /home/number/SimplyHttpServerBS/src /home/number/SimplyHttpServerBS/build /home/number/SimplyHttpServerBS/build/src /home/number/SimplyHttpServerBS/build/src/CMakeFiles/mysrc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mysrc.dir/depend

