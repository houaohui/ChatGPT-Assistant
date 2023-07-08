add_library(tts tts_common.cpp tts.cpp)


# 代码中想要调用MathFunctions中的函数，就需要#include对应的代码路径，
# 然而MathFunctions本身不需要#include，所以这里采用INTERFACE来满足该需求，
# 将MathFunctions中的CMakeLists.txt更改为
# 同时我们可以将上层目录中的CMakeLists.txt中的EXTRA_INCLUDE变量去掉，
# 同时将其从target_include_directories中删除
target_link_libraries(tts INTERFACE curl)
target_include_directories(tts INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}) 


# 添加install规则
# 这样我们在执行cmake..&&make install之后，指定的库、头文件和目标文件就安装到指定的目录中
# install(TARGETS MathFunctions DESTINATION lib) 
# install(FILES MathFunctions.h DESTINATION include) 

