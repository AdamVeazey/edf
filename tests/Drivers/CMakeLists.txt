add_executable(
    drivers_unit_tests
    RTC/DS3231Tests.cpp
)

target_compile_options( drivers_unit_tests PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( drivers_unit_tests PRIVATE ${CMAKE_LINKER_FLAGS_COMMON} )

target_link_libraries(drivers_unit_tests
    PRIVATE
        EDF
        PeripheralMocks
        gtest_main
)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(drivers_unit_tests
    PROPERTIES
        LABELS "Drivers"
    DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
        240
)