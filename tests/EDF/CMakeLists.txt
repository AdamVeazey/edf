add_executable(
    edf_unit_tests
    ArrayTests.cpp
    AssertTests.cpp
    BitFieldTests.cpp
    ColorTests.cpp
    HeapTests.cpp
    MathTests.cpp
    QueueTests.cpp
    StackTests.cpp
    StringTests.cpp
    VectorTests.cpp
    VersionTests.cpp
)

target_link_libraries(edf_unit_tests
    PRIVATE
        EDF
        gtest_main
)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(edf_unit_tests
    PROPERTIES
        LABELS "EDF"
    DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
        240
)