cmake_minimum_required(VERSION 3.10) 

# 设定工程名和版本号 
project(chat_ui VERSION 1.0) 

# specify the C++ standard 
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 
set(CMAKE_C_COMPILER "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++")
set(CMAKE_CROSSCOMPILING TRUE)
set(CAMKE_SYSTEM_NAME Linux)
set(CMAKE_FIND_ROOT_PATH "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/libs" "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/include")

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_VERBOSE_MAKEFILE ON)




# 链接 paho mqtt
link_directories(./paho-mqtt-c-1.3.12/lib)
include_directories(./paho-mqtt-c-1.3.12/include)
link_libraries(paho-mqtt3c)

# 链接 pthread
link_libraries(pthread)


# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# 链接 freetype
link_directories(./freetype-2.8/lib)
link_libraries(freetype)

# 链接 zlib freetype库需要
link_directories(/home/hah/Downloads/zlib-1.2.11/build/install/lib)
link_libraries(z)


add_subdirectory(src)
add_subdirectory(mqtt-client)
