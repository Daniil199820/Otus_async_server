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
CMAKE_SOURCE_DIR = /home/daniil/cpp/Otus_async_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniil/cpp/Otus_async_server/.gitignore

# Include any dependencies generated for this target.
include CMakeFiles/bulk_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bulk_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bulk_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bulk_server.dir/flags.make

CMakeFiles/bulk_server.dir/main.cpp.o: CMakeFiles/bulk_server.dir/flags.make
CMakeFiles/bulk_server.dir/main.cpp.o: ../main.cpp
CMakeFiles/bulk_server.dir/main.cpp.o: CMakeFiles/bulk_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniil/cpp/Otus_async_server/.gitignore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bulk_server.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bulk_server.dir/main.cpp.o -MF CMakeFiles/bulk_server.dir/main.cpp.o.d -o CMakeFiles/bulk_server.dir/main.cpp.o -c /home/daniil/cpp/Otus_async_server/main.cpp

CMakeFiles/bulk_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bulk_server.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniil/cpp/Otus_async_server/main.cpp > CMakeFiles/bulk_server.dir/main.cpp.i

CMakeFiles/bulk_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bulk_server.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniil/cpp/Otus_async_server/main.cpp -o CMakeFiles/bulk_server.dir/main.cpp.s

# Object files for target bulk_server
bulk_server_OBJECTS = \
"CMakeFiles/bulk_server.dir/main.cpp.o"

# External object files for target bulk_server
bulk_server_EXTERNAL_OBJECTS =

bulk_server: CMakeFiles/bulk_server.dir/main.cpp.o
bulk_server: CMakeFiles/bulk_server.dir/build.make
bulk_server: libasync.so
bulk_server: CMakeFiles/bulk_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniil/cpp/Otus_async_server/.gitignore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bulk_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bulk_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bulk_server.dir/build: bulk_server
.PHONY : CMakeFiles/bulk_server.dir/build

CMakeFiles/bulk_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bulk_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bulk_server.dir/clean

CMakeFiles/bulk_server.dir/depend:
	cd /home/daniil/cpp/Otus_async_server/.gitignore && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniil/cpp/Otus_async_server /home/daniil/cpp/Otus_async_server /home/daniil/cpp/Otus_async_server/.gitignore /home/daniil/cpp/Otus_async_server/.gitignore /home/daniil/cpp/Otus_async_server/.gitignore/CMakeFiles/bulk_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bulk_server.dir/depend

