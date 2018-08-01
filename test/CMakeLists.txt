if(${CMAKE_MAJOR_VERSION} GREATER_EQUAL 3 AND ${CMAKE_MINOR_VERSION} GREATER_EQUAL 9)
    cmake_policy(SET CMP0053 NEW)
    cmake_policy(SET CMP0057 NEW)

    include(GoogleTest)
endif()

include_directories(${CURL_INCLUDE_DIRS})

aux_source_directory(. SOURCE)
add_executable(${PROJECT_NAME}.test ${SOURCE})

target_link_libraries(${PROJECT_NAME}.test ${PROJECT_NAME}
                                           ${GTEST_BOTH_LIBRARIES}
                                           gmock)

gtest_add_tests(${PROJECT_NAME}.test "" ${SOURCE})
