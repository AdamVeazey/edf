add_executable( Vector main.cpp)
target_compile_options( Vector PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Vector PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Vector PRIVATE EDF )
