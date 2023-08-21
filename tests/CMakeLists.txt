include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  DOWNLOAD_EXTRACT_TIMESTAMP true
  # URL https://github.com/google/googletest/archive/release-1.12.0.tar.gz
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# add_subdirectory(Drivers)
add_subdirectory(EDF)
# add_subdirectory(MCU)
# add_subdirectory(Peripherals)
