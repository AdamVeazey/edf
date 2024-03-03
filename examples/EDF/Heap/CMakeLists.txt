add_executable( Heap main.cpp )
target_compile_options( Heap PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Heap PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Heap PRIVATE EDF )
