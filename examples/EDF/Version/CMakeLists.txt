add_executable( Version main.cpp )
target_compile_options( Version PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Version PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Version PRIVATE EDF )
