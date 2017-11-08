include_directories(${CURL_INCLUDE_DIRS})

aux_source_directory(. SOURCES)
aux_source_directory(_internal SOURCES)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${HEADERS_DIR}>)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${HEADERS_DIR})
install(DIRECTORY ${PROJECT_BINARYE_DIR} DESTINATION ${HEADERS_DIR}
        FILES_MATCHING PATTERN "*.h")
