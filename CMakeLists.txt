cmake_minimum_required(VERSION 2.8)
project(timestamp-cpp)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Options
option( TEST_ENABLED "Enable autotests build" OFF )
option( EXAMPLE_BUILD "Build example applications" OFF )

## We have to use C++11
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

## Warning all with every compiler
if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(MSVC)
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
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

add_subdirectory(src)

# Tests
if (TEST_ENABLED)
    enable_testing ()

    add_subdirectory(tests)
    add_test( Name LibraryTests COMMAND tests/tests)
endif()

# Samples
if (EXAMPLE_BUILD)
    add_subdirectory(examples)
endif()
