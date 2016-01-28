cmake_minimum_required(VERSION 2.8)
project(TimeStamp-cpp)

# Options
option( TEST_ENABLED "Enable autotests build" OFF )
option( EXAMPLE_BUILD "Build example applications" OFF )

## We have to use C++11
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

## Warning all with every compiler
if( CMAKE_BUILD_TYPE MATCHES Debug )
    if( MSVC )
        if( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
            string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
        else()
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
        endif()
    elseif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic" )
    endif()
endif()

set( BOOST_COMPONENTS system)

if( TEST_ENABLED )
    set( BOOST_COMPONENTS unit_test_framework
                          ${BOOST_COMPONENTS}
        )
endif()

find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS} )

if(NOT Boost_SYSTEM_FOUND)
    message( FATAL_ERROR "boost.system must be installed")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

add_subdirectory(src)

# Tests
if ( TEST_ENABLED )
    if(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND )
        message( FATAL_ERROR "boost.unit_test_framework must be installed")
    endif()

    add_subdirectory(tests)

    enable_testing ()
    add_test( Name LibraryTests COMMAND tests/tests)
endif()

# Samples
if ( EXAMPLE_BUILD )
    add_subdirectory(examples)
endif()
