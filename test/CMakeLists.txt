if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER_EQUAL 3.9)
    cmake_policy(SET CMP0053 NEW)
    cmake_policy(SET CMP0057 NEW)

    include(GoogleTest)
endif()

include_directories(${GTEST_INCLUDE_DIRS})

aux_source_directory(. SOURCE)
add_executable(${PROJECT_NAME}.test ${SOURCE})

target_link_libraries(${PROJECT_NAME}.test ${PROJECT_NAME}
                                           ${GTEST_BOTH_LIBRARIES})

gtest_add_tests(${PROJECT_NAME}.test "" ${SOURCE})
