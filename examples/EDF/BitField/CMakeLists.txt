add_executable( BitField main.cpp)
target_compile_options( BitField PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( BitField PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( BitField PRIVATE EDF )
