add_executable( Color main.cpp)
target_compile_options( Color PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Color PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Color PRIVATE EDF )
