add_library(asr asr.cpp common.cpp)


target_link_libraries(asr PUBLIC json)
target_include_directories(asr PUBLIC INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}) 


