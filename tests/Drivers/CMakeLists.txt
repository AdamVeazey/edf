# add_executable(
#     drivers_unit_tests
#     GPIOTests.cpp
# )

# target_link_libraries(drivers_unit_tests
#     PRIVATE
#         EDF
#         Peripherals
#         Drivers
#         gtest_main
# )

# # automatic discovery of unit tests
# include(GoogleTest)
# gtest_discover_tests(drivers_unit_tests
#     PROPERTIES
#         LABELS "Drivers"
#     DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
#         240
# )