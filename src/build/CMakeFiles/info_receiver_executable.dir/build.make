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
CMAKE_SOURCE_DIR = /home/sokee/workspace/Monitor-Inband-Getter/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sokee/workspace/Monitor-Inband-Getter/src/build

# Include any dependencies generated for this target.
include CMakeFiles/info_receiver_executable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/info_receiver_executable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/info_receiver_executable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/info_receiver_executable.dir/flags.make

CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o: CMakeFiles/info_receiver_executable.dir/flags.make
CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o: ../Info_Receiver.cpp
CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o: CMakeFiles/info_receiver_executable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sokee/workspace/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o -MF CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o.d -o CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o -c /home/sokee/workspace/Monitor-Inband-Getter/src/Info_Receiver.cpp

CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sokee/workspace/Monitor-Inband-Getter/src/Info_Receiver.cpp > CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.i

CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sokee/workspace/Monitor-Inband-Getter/src/Info_Receiver.cpp -o CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.s

# Object files for target info_receiver_executable
info_receiver_executable_OBJECTS = \
"CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o"

# External object files for target info_receiver_executable
info_receiver_executable_EXTERNAL_OBJECTS =

info_receiver_executable: CMakeFiles/info_receiver_executable.dir/Info_Receiver.cpp.o
info_receiver_executable: CMakeFiles/info_receiver_executable.dir/build.make
info_receiver_executable: libmy_lib.a
info_receiver_executable: CMakeFiles/info_receiver_executable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sokee/workspace/Monitor-Inband-Getter/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable info_receiver_executable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/info_receiver_executable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/info_receiver_executable.dir/build: info_receiver_executable
.PHONY : CMakeFiles/info_receiver_executable.dir/build

CMakeFiles/info_receiver_executable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/info_receiver_executable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/info_receiver_executable.dir/clean

CMakeFiles/info_receiver_executable.dir/depend:
	cd /home/sokee/workspace/Monitor-Inband-Getter/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sokee/workspace/Monitor-Inband-Getter/src /home/sokee/workspace/Monitor-Inband-Getter/src /home/sokee/workspace/Monitor-Inband-Getter/src/build /home/sokee/workspace/Monitor-Inband-Getter/src/build /home/sokee/workspace/Monitor-Inband-Getter/src/build/CMakeFiles/info_receiver_executable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/info_receiver_executable.dir/depend

