# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\16997\Desktop\chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\16997\Desktop\chat\build

# Include any dependencies generated for this target.
include mqtt-client/CMakeFiles/mqtt-client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mqtt-client/CMakeFiles/mqtt-client.dir/compiler_depend.make

# Include the progress variables for this target.
include mqtt-client/CMakeFiles/mqtt-client.dir/progress.make

# Include the compile flags for this target's objects.
include mqtt-client/CMakeFiles/mqtt-client.dir/flags.make

mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj: mqtt-client/CMakeFiles/mqtt-client.dir/flags.make
mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj: mqtt-client/CMakeFiles/mqtt-client.dir/includes_CXX.rsp
mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj: C:/Users/16997/Desktop/chat/mqtt-client/mqtt-client.cpp
mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj: mqtt-client/CMakeFiles/mqtt-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\16997\Desktop\chat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj"
	cd /d C:\Users\16997\Desktop\chat\build\mqtt-client && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj -MF CMakeFiles\mqtt-client.dir\mqtt-client.cpp.obj.d -o CMakeFiles\mqtt-client.dir\mqtt-client.cpp.obj -c C:\Users\16997\Desktop\chat\mqtt-client\mqtt-client.cpp

mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mqtt-client.dir/mqtt-client.cpp.i"
	cd /d C:\Users\16997\Desktop\chat\build\mqtt-client && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\16997\Desktop\chat\mqtt-client\mqtt-client.cpp > CMakeFiles\mqtt-client.dir\mqtt-client.cpp.i

mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mqtt-client.dir/mqtt-client.cpp.s"
	cd /d C:\Users\16997\Desktop\chat\build\mqtt-client && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\16997\Desktop\chat\mqtt-client\mqtt-client.cpp -o CMakeFiles\mqtt-client.dir\mqtt-client.cpp.s

# Object files for target mqtt-client
mqtt__client_OBJECTS = \
"CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj"

# External object files for target mqtt-client
mqtt__client_EXTERNAL_OBJECTS =

mqtt-client/libmqtt-client.a: mqtt-client/CMakeFiles/mqtt-client.dir/mqtt-client.cpp.obj
mqtt-client/libmqtt-client.a: mqtt-client/CMakeFiles/mqtt-client.dir/build.make
mqtt-client/libmqtt-client.a: mqtt-client/CMakeFiles/mqtt-client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\16997\Desktop\chat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmqtt-client.a"
	cd /d C:\Users\16997\Desktop\chat\build\mqtt-client && $(CMAKE_COMMAND) -P CMakeFiles\mqtt-client.dir\cmake_clean_target.cmake
	cd /d C:\Users\16997\Desktop\chat\build\mqtt-client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mqtt-client.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mqtt-client/CMakeFiles/mqtt-client.dir/build: mqtt-client/libmqtt-client.a
.PHONY : mqtt-client/CMakeFiles/mqtt-client.dir/build

mqtt-client/CMakeFiles/mqtt-client.dir/clean:
	cd /d C:\Users\16997\Desktop\chat\build\mqtt-client && $(CMAKE_COMMAND) -P CMakeFiles\mqtt-client.dir\cmake_clean.cmake
.PHONY : mqtt-client/CMakeFiles/mqtt-client.dir/clean

mqtt-client/CMakeFiles/mqtt-client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\16997\Desktop\chat C:\Users\16997\Desktop\chat\mqtt-client C:\Users\16997\Desktop\chat\build C:\Users\16997\Desktop\chat\build\mqtt-client C:\Users\16997\Desktop\chat\build\mqtt-client\CMakeFiles\mqtt-client.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : mqtt-client/CMakeFiles/mqtt-client.dir/depend

