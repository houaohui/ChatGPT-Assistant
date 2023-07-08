
add_executable(chat offline_wkup.cpp time.cpp main.cpp) 




list(APPEND EXTRA_LIBS tts)
list(APPEND EXTRA_LIBS json)
list(APPEND EXTRA_LIBS asr)
list(APPEND EXTRA_LIBS audio_rec)
list(APPEND EXTRA_LIBS mqtt-client)


target_link_libraries(chat PUBLIC ${EXTRA_LIBS})


# target_include_directories(chat PUBLIC 
#                            "${PROJECT_BINARY_DIR}" 
#                         #    "${EXTRA_INCLUDES}" 
#                            ) 
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/asr)
include_directories(${PROJECT_SOURCE_DIR}/tts)
include_directories(${PROJECT_SOURCE_DIR}/mqtt-client)




