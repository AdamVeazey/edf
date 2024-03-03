add_executable( "String" main.cpp)
target_compile_options( "String" PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( "String" PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( "String" PRIVATE EDF )

