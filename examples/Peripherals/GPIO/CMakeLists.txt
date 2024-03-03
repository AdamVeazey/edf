add_executable( GPIO main.cpp)
target_compile_options( GPIO PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( GPIO PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( GPIO PRIVATE EDF Peripherals )
