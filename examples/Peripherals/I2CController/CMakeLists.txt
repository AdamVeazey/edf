add_executable( I2CController main.cpp )
target_compile_options( I2CController PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( I2CController PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( I2CController PRIVATE EDF Peripherals )
