# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build

# Include any dependencies generated for this target.
include src/CMakeFiles/chat_ui.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/chat_ui.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/chat_ui.dir/flags.make

src/CMakeFiles/chat_ui.dir/freetype_draw.c.o: src/CMakeFiles/chat_ui.dir/flags.make
src/CMakeFiles/chat_ui.dir/freetype_draw.c.o: ../src/freetype_draw.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/chat_ui.dir/freetype_draw.c.o"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chat_ui.dir/freetype_draw.c.o   -c /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/freetype_draw.c

src/CMakeFiles/chat_ui.dir/freetype_draw.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chat_ui.dir/freetype_draw.c.i"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/freetype_draw.c > CMakeFiles/chat_ui.dir/freetype_draw.c.i

src/CMakeFiles/chat_ui.dir/freetype_draw.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chat_ui.dir/freetype_draw.c.s"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/freetype_draw.c -o CMakeFiles/chat_ui.dir/freetype_draw.c.s

src/CMakeFiles/chat_ui.dir/TXT_Viewer.c.o: src/CMakeFiles/chat_ui.dir/flags.make
src/CMakeFiles/chat_ui.dir/TXT_Viewer.c.o: ../src/TXT_Viewer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/chat_ui.dir/TXT_Viewer.c.o"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chat_ui.dir/TXT_Viewer.c.o   -c /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/TXT_Viewer.c

src/CMakeFiles/chat_ui.dir/TXT_Viewer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chat_ui.dir/TXT_Viewer.c.i"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/TXT_Viewer.c > CMakeFiles/chat_ui.dir/TXT_Viewer.c.i

src/CMakeFiles/chat_ui.dir/TXT_Viewer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chat_ui.dir/TXT_Viewer.c.s"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/TXT_Viewer.c -o CMakeFiles/chat_ui.dir/TXT_Viewer.c.s

src/CMakeFiles/chat_ui.dir/main.cpp.o: src/CMakeFiles/chat_ui.dir/flags.make
src/CMakeFiles/chat_ui.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/chat_ui.dir/main.cpp.o"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chat_ui.dir/main.cpp.o -c /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/main.cpp

src/CMakeFiles/chat_ui.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat_ui.dir/main.cpp.i"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/main.cpp > CMakeFiles/chat_ui.dir/main.cpp.i

src/CMakeFiles/chat_ui.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat_ui.dir/main.cpp.s"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src/main.cpp -o CMakeFiles/chat_ui.dir/main.cpp.s

# Object files for target chat_ui
chat_ui_OBJECTS = \
"CMakeFiles/chat_ui.dir/freetype_draw.c.o" \
"CMakeFiles/chat_ui.dir/TXT_Viewer.c.o" \
"CMakeFiles/chat_ui.dir/main.cpp.o"

# External object files for target chat_ui
chat_ui_EXTERNAL_OBJECTS =

src/chat_ui: src/CMakeFiles/chat_ui.dir/freetype_draw.c.o
src/chat_ui: src/CMakeFiles/chat_ui.dir/TXT_Viewer.c.o
src/chat_ui: src/CMakeFiles/chat_ui.dir/main.cpp.o
src/chat_ui: src/CMakeFiles/chat_ui.dir/build.make
src/chat_ui: mqtt-client/libmqtt-client.a
src/chat_ui: src/CMakeFiles/chat_ui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable chat_ui"
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chat_ui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/chat_ui.dir/build: src/chat_ui

.PHONY : src/CMakeFiles/chat_ui.dir/build

src/CMakeFiles/chat_ui.dir/clean:
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src && $(CMAKE_COMMAND) -P CMakeFiles/chat_ui.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/chat_ui.dir/clean

src/CMakeFiles/chat_ui.dir/depend:
	cd /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/src /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src /home/hah/Desktop/ChatGPT-Assistent/ChatGPT-Assistant/source/Linux/chat-ui/build/src/CMakeFiles/chat_ui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/chat_ui.dir/depend

