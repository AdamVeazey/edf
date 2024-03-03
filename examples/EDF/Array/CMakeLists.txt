add_executable( Array main.cpp)
target_compile_options( Array PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( Array PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( Array PRIVATE EDF )
