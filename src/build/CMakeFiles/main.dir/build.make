# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/sokee/Desktop/Monitor-Inband-Getter/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sokee/Desktop/Monitor-Inband-Getter/src/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: ../main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /home/sokee/Desktop/Monitor-Inband-Getter/src/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sokee/Desktop/Monitor-Inband-Getter/src/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sokee/Desktop/Monitor-Inband-Getter/src/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/tools.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/tools.cpp.o: ../tools.cpp
CMakeFiles/main.dir/tools.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/tools.cpp.o -MF CMakeFiles/main.dir/tools.cpp.o.d -o CMakeFiles/main.dir/tools.cpp.o -c /home/sokee/Desktop/Monitor-Inband-Getter/src/tools.cpp

CMakeFiles/main.dir/tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sokee/Desktop/Monitor-Inband-Getter/src/tools.cpp > CMakeFiles/main.dir/tools.cpp.i

CMakeFiles/main.dir/tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sokee/Desktop/Monitor-Inband-Getter/src/tools.cpp -o CMakeFiles/main.dir/tools.cpp.s

CMakeFiles/main.dir/jsonPackage.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/jsonPackage.cpp.o: ../jsonPackage.cpp
CMakeFiles/main.dir/jsonPackage.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/jsonPackage.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/jsonPackage.cpp.o -MF CMakeFiles/main.dir/jsonPackage.cpp.o.d -o CMakeFiles/main.dir/jsonPackage.cpp.o -c /home/sokee/Desktop/Monitor-Inband-Getter/src/jsonPackage.cpp

CMakeFiles/main.dir/jsonPackage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/jsonPackage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sokee/Desktop/Monitor-Inband-Getter/src/jsonPackage.cpp > CMakeFiles/main.dir/jsonPackage.cpp.i

CMakeFiles/main.dir/jsonPackage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/jsonPackage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sokee/Desktop/Monitor-Inband-Getter/src/jsonPackage.cpp -o CMakeFiles/main.dir/jsonPackage.cpp.s

CMakeFiles/main.dir/Procps.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/Procps.cpp.o: ../Procps.cpp
CMakeFiles/main.dir/Procps.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/Procps.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/Procps.cpp.o -MF CMakeFiles/main.dir/Procps.cpp.o.d -o CMakeFiles/main.dir/Procps.cpp.o -c /home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.cpp

CMakeFiles/main.dir/Procps.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/Procps.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.cpp > CMakeFiles/main.dir/Procps.cpp.i

CMakeFiles/main.dir/Procps.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/Procps.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.cpp -o CMakeFiles/main.dir/Procps.cpp.s

CMakeFiles/main.dir/Boost_process.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/Boost_process.cpp.o: ../Boost_process.cpp
CMakeFiles/main.dir/Boost_process.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/Boost_process.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/Boost_process.cpp.o -MF CMakeFiles/main.dir/Boost_process.cpp.o.d -o CMakeFiles/main.dir/Boost_process.cpp.o -c /home/sokee/Desktop/Monitor-Inband-Getter/src/Boost_process.cpp

CMakeFiles/main.dir/Boost_process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/Boost_process.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sokee/Desktop/Monitor-Inband-Getter/src/Boost_process.cpp > CMakeFiles/main.dir/Boost_process.cpp.i

CMakeFiles/main.dir/Boost_process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/Boost_process.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sokee/Desktop/Monitor-Inband-Getter/src/Boost_process.cpp -o CMakeFiles/main.dir/Boost_process.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/tools.cpp.o" \
"CMakeFiles/main.dir/jsonPackage.cpp.o" \
"CMakeFiles/main.dir/Procps.cpp.o" \
"CMakeFiles/main.dir/Boost_process.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/tools.cpp.o
main: CMakeFiles/main.dir/jsonPackage.cpp.o
main: CMakeFiles/main.dir/Procps.cpp.o
main: CMakeFiles/main.dir/Boost_process.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/lib/x86_64-linux-gnu/libprocps.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/sokee/Desktop/Monitor-Inband-Getter/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sokee/Desktop/Monitor-Inband-Getter/src /home/sokee/Desktop/Monitor-Inband-Getter/src /home/sokee/Desktop/Monitor-Inband-Getter/src/build /home/sokee/Desktop/Monitor-Inband-Getter/src/build /home/sokee/Desktop/Monitor-Inband-Getter/src/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
