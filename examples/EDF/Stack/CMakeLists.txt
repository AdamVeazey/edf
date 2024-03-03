add_executable( Stack main.cpp)
target_compile_options( Stack PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Stack PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Stack PRIVATE EDF )
