add_library( Peripherals INTERFACE )

target_compile_features( Peripherals INTERFACE cxx_std_17 )

target_include_directories( Peripherals
                            INTERFACE
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/src
)