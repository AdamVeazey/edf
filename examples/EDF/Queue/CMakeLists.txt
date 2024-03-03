add_executable( Queue main.cpp)
target_compile_options( Queue PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Queue PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Queue PRIVATE EDF )
