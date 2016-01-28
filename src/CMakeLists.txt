include_directories( .
                     include )

aux_source_directory( . SOURCES )


add_library( timestamp-cpp SHARED ${SOURCES} )

target_link_libraries( timestamp-cpp
                       ${Boost_SYSTEM_LIBRARY}
                      )
