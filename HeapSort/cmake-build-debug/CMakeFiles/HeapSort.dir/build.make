# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/HeapSort.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/HeapSort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HeapSort.dir/flags.make

CMakeFiles/HeapSort.dir/main.cpp.obj: CMakeFiles/HeapSort.dir/flags.make
CMakeFiles/HeapSort.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HeapSort.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HeapSort.dir\main.cpp.obj -c "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\main.cpp"

CMakeFiles/HeapSort.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HeapSort.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\main.cpp" > CMakeFiles\HeapSort.dir\main.cpp.i

CMakeFiles/HeapSort.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HeapSort.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\main.cpp" -o CMakeFiles\HeapSort.dir\main.cpp.s

# Object files for target HeapSort
HeapSort_OBJECTS = \
"CMakeFiles/HeapSort.dir/main.cpp.obj"

# External object files for target HeapSort
HeapSort_EXTERNAL_OBJECTS =

HeapSort.exe: CMakeFiles/HeapSort.dir/main.cpp.obj
HeapSort.exe: CMakeFiles/HeapSort.dir/build.make
HeapSort.exe: CMakeFiles/HeapSort.dir/linklibs.rsp
HeapSort.exe: CMakeFiles/HeapSort.dir/objects1.rsp
HeapSort.exe: CMakeFiles/HeapSort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HeapSort.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HeapSort.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HeapSort.dir/build: HeapSort.exe
.PHONY : CMakeFiles/HeapSort.dir/build

CMakeFiles/HeapSort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HeapSort.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HeapSort.dir/clean

CMakeFiles/HeapSort.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort" "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort" "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\cmake-build-debug" "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\cmake-build-debug" "D:\Facultate\Anul 2\Semestrul 1\AF\Lab2\HeapSort\cmake-build-debug\CMakeFiles\HeapSort.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/HeapSort.dir/depend

