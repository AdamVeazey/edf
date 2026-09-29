add_library( PeripheralMocks STATIC )

target_compile_features( PeripheralMocks PUBLIC cxx_std_17 )

target_include_directories( PeripheralMocks
                            PUBLIC
                            "."
)

target_sources( PeripheralMocks
                PRIVATE
                "I2CControllerMock.cpp"
)

target_link_libraries(PeripheralMocks PRIVATE EDF)

# add_executable(
#     peripherals_unit_tests
#     GPIOTests.cpp
# )

# target_link_libraries(peripherals_unit_tests
#     PRIVATE
#         EDF
#         Peripherals
#         gtest_main
# )

# # automatic discovery of unit tests
# include(GoogleTest)
# gtest_discover_tests(peripherals_unit_tests
#     PROPERTIES
#         LABELS "Peripherals"
#     DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
#         240
# )