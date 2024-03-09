add_executable( SPIController main.cpp)
target_compile_options( SPIController PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( SPIController PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( SPIController PRIVATE EDF Peripherals )
