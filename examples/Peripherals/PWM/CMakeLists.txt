add_executable( PWM main.cpp )
target_compile_options( PWM PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( PWM PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )
target_link_libraries( PWM PRIVATE EDF Peripherals )
