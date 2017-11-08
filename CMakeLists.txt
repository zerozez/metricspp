cmake_minimum_required(VERSION 2.8)
project(metricspp C CXX)

option(BUILD_TESTS "Build unit tests for the library" OFF)

set(MAJOR_VER 0)
set(MINOR_VER 1)
set(PATCH_VER 0)

set(HEADERS_DIR include/metricspp)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set (CMAKE_CXX_STANDARD 11)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(MSVC)
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4"
                   CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
        endif()
    elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall -Wno-long-long -pedantic")
    endif()
else()
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0 /Ox")
    elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g0 -Os")
    endif()
endif()

# Curl library
find_package(CURL)

if(NOT CURL_FOUND)
    message(WARN "Using project's curl library ....")

    set(BUILD_CURL_EXE OFF CACHE BOOL "No curl exe build")
    set(BUILD_TESTING OFF CACHE BOOL "No curl tests buld")
    add_subdirectory(lib/curl EXCLUDE_FROM_ALL)

    set(CURL_FOUND TRUE)
    set(CURL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/curl/include)
    set(CURL_LIBRARIES libcurl)

endif()

add_subdirectory(src)

if(BUILD_TESTS)
    find_package(GTest)

    if(NOT GTEST_FOUND)
        message(STATUS
             "Not using system gtest, using built-in googletest project instead.")
    
        set(BUILD_GTEST ON)
        add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

        set(GTEST_FOUND TRUE)
        set(GTEST_LIBRARIES gtest)
        set(GTEST_MAIN_LIBRARIES gtest_main)
        set(GTEST_BOTH_LIBRARIES gtest gtest_main)
        set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)

        # Group under the "tests/gtest" project folder in IDEs such as Visual Studio.
        set_property(TARGET gtest PROPERTY FOLDER "tests/gtest")
        set_property(TARGET gtest_main PROPERTY FOLDER "tests/gtest")
    endif()

    enable_testing()
    add_subdirectory(test)
endif()
