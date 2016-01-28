include_directories( .
                     ${CMAKE_SOURCE_DIR}/src/include )

add_executable( example_influx ex_influx.cc )
target_link_libraries( example_influx timestamp-cpp )
