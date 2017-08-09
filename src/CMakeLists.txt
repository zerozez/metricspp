set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})

aux_source_directory(. SOURCES)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME}
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${Boost_LIBRARIES})
