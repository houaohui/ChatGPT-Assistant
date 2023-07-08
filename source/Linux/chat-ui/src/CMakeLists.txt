
add_executable(chat_ui freetype_draw.c TXT_Viewer.c main.cpp) 




list(APPEND EXTRA_LIBS mqtt-client)


target_link_libraries(chat_ui PUBLIC ${EXTRA_LIBS})


target_include_directories(chat_ui PUBLIC ${PROJECT_SOURCE_DIR}/freetype-2.8/include/freetype2)
target_include_directories(chat_ui PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(chat_ui PUBLIC ${PROJECT_SOURCE_DIR}/mqtt-client)


# target_include_directories(chat PUBLIC 
#                            "${PROJECT_BINARY_DIR}" 
#                         #    "${EXTRA_INCLUDES}" 
#                            ) 
# include_directories(${PROJECT_SOURCE_DIR}/freetype-2.8/include)
# include_directories(${PROJECT_SOURCE_DIR}/asr)
# include_directories(${PROJECT_SOURCE_DIR}/tts)
# include_directories(${PROJECT_SOURCE_DIR}/mqtt-client)



