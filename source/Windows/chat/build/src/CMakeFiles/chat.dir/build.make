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
include src/CMakeFiles/chat.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/chat.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/chat.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/chat.dir/flags.make

src/CMakeFiles/chat.dir/offline_wkup.cpp.obj: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/offline_wkup.cpp.obj: src/CMakeFiles/chat.dir/includes_CXX.rsp
src/CMakeFiles/chat.dir/offline_wkup.cpp.obj: C:/Users/16997/Desktop/chat/src/offline_wkup.cpp
src/CMakeFiles/chat.dir/offline_wkup.cpp.obj: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\16997\Desktop\chat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/chat.dir/offline_wkup.cpp.obj"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/offline_wkup.cpp.obj -MF CMakeFiles\chat.dir\offline_wkup.cpp.obj.d -o CMakeFiles\chat.dir\offline_wkup.cpp.obj -c C:\Users\16997\Desktop\chat\src\offline_wkup.cpp

src/CMakeFiles/chat.dir/offline_wkup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/offline_wkup.cpp.i"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\16997\Desktop\chat\src\offline_wkup.cpp > CMakeFiles\chat.dir\offline_wkup.cpp.i

src/CMakeFiles/chat.dir/offline_wkup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/offline_wkup.cpp.s"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\16997\Desktop\chat\src\offline_wkup.cpp -o CMakeFiles\chat.dir\offline_wkup.cpp.s

src/CMakeFiles/chat.dir/time.cpp.obj: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/time.cpp.obj: src/CMakeFiles/chat.dir/includes_CXX.rsp
src/CMakeFiles/chat.dir/time.cpp.obj: C:/Users/16997/Desktop/chat/src/time.cpp
src/CMakeFiles/chat.dir/time.cpp.obj: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\16997\Desktop\chat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/chat.dir/time.cpp.obj"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/time.cpp.obj -MF CMakeFiles\chat.dir\time.cpp.obj.d -o CMakeFiles\chat.dir\time.cpp.obj -c C:\Users\16997\Desktop\chat\src\time.cpp

src/CMakeFiles/chat.dir/time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/time.cpp.i"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\16997\Desktop\chat\src\time.cpp > CMakeFiles\chat.dir\time.cpp.i

src/CMakeFiles/chat.dir/time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/time.cpp.s"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\16997\Desktop\chat\src\time.cpp -o CMakeFiles\chat.dir\time.cpp.s

src/CMakeFiles/chat.dir/main.cpp.obj: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/main.cpp.obj: src/CMakeFiles/chat.dir/includes_CXX.rsp
src/CMakeFiles/chat.dir/main.cpp.obj: C:/Users/16997/Desktop/chat/src/main.cpp
src/CMakeFiles/chat.dir/main.cpp.obj: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\16997\Desktop\chat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/chat.dir/main.cpp.obj"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/main.cpp.obj -MF CMakeFiles\chat.dir\main.cpp.obj.d -o CMakeFiles\chat.dir\main.cpp.obj -c C:\Users\16997\Desktop\chat\src\main.cpp

src/CMakeFiles/chat.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/main.cpp.i"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\16997\Desktop\chat\src\main.cpp > CMakeFiles\chat.dir\main.cpp.i

src/CMakeFiles/chat.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/main.cpp.s"
	cd /d C:\Users\16997\Desktop\chat\build\src && D:\w64devkit-1.18.0\w64devkit\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\16997\Desktop\chat\src\main.cpp -o CMakeFiles\chat.dir\main.cpp.s

# Object files for target chat
chat_OBJECTS = \
"CMakeFiles/chat.dir/offline_wkup.cpp.obj" \
"CMakeFiles/chat.dir/time.cpp.obj" \
"CMakeFiles/chat.dir/main.cpp.obj"

# External object files for target chat
chat_EXTERNAL_OBJECTS =

src/chat.exe: src/CMakeFiles/chat.dir/offline_wkup.cpp.obj
src/chat.exe: src/CMakeFiles/chat.dir/time.cpp.obj
src/chat.exe: src/CMakeFiles/chat.dir/main.cpp.obj
src/chat.exe: src/CMakeFiles/chat.dir/build.make
src/chat.exe: tts/libtts.a
src/chat.exe: json/libjson.a
src/chat.exe: asr/libasr.a
src/chat.exe: audiorecorder/libaudio_rec.a
src/chat.exe: mqtt-client/libmqtt-client.a
src/chat.exe: json/libjson.a
src/chat.exe: src/CMakeFiles/chat.dir/linkLibs.rsp
src/chat.exe: src/CMakeFiles/chat.dir/objects1
src/chat.exe: src/CMakeFiles/chat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\16997\Desktop\chat\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable chat.exe"
	cd /d C:\Users\16997\Desktop\chat\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\chat.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/chat.dir/build: src/chat.exe
.PHONY : src/CMakeFiles/chat.dir/build

src/CMakeFiles/chat.dir/clean:
	cd /d C:\Users\16997\Desktop\chat\build\src && $(CMAKE_COMMAND) -P CMakeFiles\chat.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/chat.dir/clean

src/CMakeFiles/chat.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\16997\Desktop\chat C:\Users\16997\Desktop\chat\src C:\Users\16997\Desktop\chat\build C:\Users\16997\Desktop\chat\build\src C:\Users\16997\Desktop\chat\build\src\CMakeFiles\chat.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/chat.dir/depend

