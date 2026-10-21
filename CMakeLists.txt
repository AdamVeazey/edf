cmake_minimum_required(VERSION 3.16.3)

project(EDF
    VERSION 1.0.0
    DESCRIPTION "Embedded Development Framework"
    HOMEPAGE_URL "https://github.com/Veazus/edf"
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# Options (Off by default for lightweight core consumption)
# -----------------------------------------------------------------------------
option(EDF_BUILD_PERIPHERALS "Build Peripherals library"     OFF)
option(EDF_BUILD_DRIVERS     "Build Drivers library"         OFF)
option(EDF_ENABLE_LTO        "Enable Link-Time Optimization" OFF)
option(EDF_BUILD_TESTS       "Build unit tests"              OFF)
option(EDF_BUILD_EXAMPLES    "Build examples"                OFF)

# -----------------------------------------------------------------------------
# Dependency Enforcement (Auto-enable Peripherals if Drivers are requested)
# -----------------------------------------------------------------------------
if(EDF_BUILD_DRIVERS AND NOT EDF_BUILD_PERIPHERALS)
    message(STATUS "EDF: Drivers requested. Automatically enabling Peripherals dependency.")
    set(EDF_BUILD_PERIPHERALS ON CACHE BOOL "Build Peripherals library" FORCE)
endif()

# Track targets for installation later
set(EDF_EXPORTED_TARGETS "")

# -----------------------------------------------------------------------------
# Common Flags & Settings Helper
# -----------------------------------------------------------------------------
set(EDF_WARNING_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wundef
    -Wconversion
)

set(EDF_EMBEDDED_FLAGS
    -Os
    -g3
    -fno-common
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -fno-unwind-tables
    -fno-rtti
    -fno-threadsafe-statics
)

function(edf_apply_common_settings TARGET_NAME)
    target_compile_features(${TARGET_NAME} PUBLIC
        cxx_std_17
    )

    target_include_directories(${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${EDF_WARNING_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -Wpedantic -Wconversion>
        ${EDF_EMBEDDED_FLAGS}
    )

    target_link_options(${TARGET_NAME} PRIVATE
        -Wl,--gc-sections
    )

    if(EDF_ENABLE_LTO)
        set_property(TARGET ${TARGET_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endfunction()

# -----------------------------------------------------------------------------
# Core EDF Library
# -----------------------------------------------------------------------------
add_library(EDF STATIC)

target_sources(EDF
    PRIVATE
        src/String.cpp
)

edf_apply_common_settings(EDF)

list(APPEND EDF_EXPORTED_TARGETS EDF)

# -----------------------------------------------------------------------------
# Peripherals Library (Depends on EDF)
# -----------------------------------------------------------------------------
if(EDF_BUILD_PERIPHERALS)
    add_library(Peripherals INTERFACE)

    target_compile_features(Peripherals INTERFACE
        cxx_std_17
    )

    target_include_directories(Peripherals
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # Peripherals depends on EDF (INTERFACE so consumers of Peripherals also get EDF)
    target_link_libraries(Peripherals INTERFACE EDF)
    list(APPEND EDF_EXPORTED_TARGETS Peripherals)
endif()

# -----------------------------------------------------------------------------
# Drivers Library (Depends on Peripherals, which depends on EDF)
# -----------------------------------------------------------------------------
if(EDF_BUILD_DRIVERS)
    add_library(Drivers STATIC)
    target_sources(Drivers
        PRIVATE
            src/Drivers/RTC/DS3231.cpp
            src/Drivers/LED_RGB.cpp
    )
    edf_apply_common_settings(Drivers)


    target_link_libraries(Drivers PRIVATE Peripherals)
    list(APPEND EDF_EXPORTED_TARGETS Drivers)
endif()

# -----------------------------------------------------------------------------
# Installation & Packaging
# -----------------------------------------------------------------------------
include(GNUInstallDirs)

# Install only the libraries that were actually built/enabled
install(TARGETS ${EDF_EXPORTED_TARGETS}
    EXPORT EDFTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT EDFTargets
    FILE EDFTargets.cmake
    NAMESPACE EDF::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/EDF
)

# -----------------------------------------------------------------------------
# Optional Subdirectories
# -----------------------------------------------------------------------------
if(EDF_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(EDF_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()