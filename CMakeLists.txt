cmake_minimum_required(VERSION 3.16.3)

project(EDF
    VERSION 1.1.0
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
option(EDF_BUILD_TESTS       "Build unit tests"              OFF)
option(EDF_BUILD_EXAMPLES    "Build examples"                OFF)

# Assertion Configuration Options (Defaults to fully enabled)
option(EDF_ENABLE_ASSERTS             "Enable EDF debug assertions (EDF_ASSERTD)" ON)
option(EDF_ASSERT_PRINT               "Enable assertion failure printing"         ON)
option(EDF_ASSERT_PRINT_ASSUMPTION    "Print assumption text in assertions"       ON)
option(EDF_ASSERT_PRINT_FUNCTION_NAME "Print function name in assertions"         ON)
option(EDF_ASSERT_PRINT_FILE_LINE     "Print file name and line number"           ON)

# -----------------------------------------------------------------------------
# Zephyr Kconfig Bridge (If building inside a Zephyr workspace)
# -----------------------------------------------------------------------------
if(DEFINED ZEPHYR_BASE)
    if(DEFINED CONFIG_EDF_PERIPHERALS)
        set(EDF_BUILD_PERIPHERALS ${CONFIG_EDF_PERIPHERALS})
    endif()
    if(DEFINED CONFIG_EDF_DRIVERS)
        set(EDF_BUILD_DRIVERS ${CONFIG_EDF_DRIVERS})
    endif()
    if(DEFINED CONFIG_EDF_ASSERTS)
        set(EDF_ENABLE_ASSERTS ${CONFIG_EDF_ASSERTS})
    endif()
    if(DEFINED CONFIG_EDF_ASSERT_PRINT)
        set(EDF_ASSERT_PRINT ${CONFIG_EDF_ASSERT_PRINT})
    endif()
    if(DEFINED CONFIG_EDF_ASSERT_PRINT_ASSUMPTION)
        set(EDF_ASSERT_PRINT_ASSUMPTION ${CONFIG_EDF_ASSERT_PRINT_ASSUMPTION})
    endif()
    if(DEFINED CONFIG_EDF_ASSERT_PRINT_FUNCTION_NAME)
        set(EDF_ASSERT_PRINT_FUNCTION_NAME ${CONFIG_EDF_ASSERT_PRINT_FUNCTION_NAME})
    endif()
    if(DEFINED CONFIG_EDF_ASSERT_PRINT_FILE_NAME_LINE_NUM)
        set(EDF_ASSERT_PRINT_FILE_LINE ${CONFIG_EDF_ASSERT_PRINT_FILE_NAME_LINE_NUM})
    endif()
endif()

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

function(edf_apply_common_settings TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    target_include_directories(${TARGET_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # Only apply strict warnings to our own library sources (PRIVATE)
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${EDF_WARNING_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -Wpedantic -Wconversion>
        -ffunction-sections
        -fdata-sections
        -fno-exceptions
        -fno-unwind-tables
        -fno-rtti
        -fno-threadsafe-statics
    )

    # Link Zephyr interface target if present
    if(TARGET zephyr_interface)
        target_link_libraries(${TARGET_NAME} PRIVATE zephyr_interface)
    endif()

    # Apply compile definitions based on unified options
    if(NOT EDF_ENABLE_ASSERTS)
        target_compile_definitions(${TARGET_NAME} PUBLIC NEDF_DISABLE_DEBUG_ASSERTS)
    endif()
    if(NOT EDF_ASSERT_PRINT)
        target_compile_definitions(${TARGET_NAME} PUBLIC NEDF_ASSERT_PRINT)
    endif()
    if(NOT EDF_ASSERT_PRINT_ASSUMPTION)
        target_compile_definitions(${TARGET_NAME} PUBLIC NEDF_ASSERT_PRINT_ASSUMPTION)
    endif()
    if(NOT EDF_ASSERT_PRINT_FUNCTION_NAME)
        target_compile_definitions(${TARGET_NAME} PUBLIC NEDF_ASSERT_PRINT_FUNCTION_NAME)
    endif()
    if(NOT EDF_ASSERT_PRINT_FILE_LINE)
        target_compile_definitions(${TARGET_NAME} PUBLIC NEDF_ASSERT_PRINT_FILE_NAME_LINE_NUM)
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

if(TARGET zephyr_interface)
    target_sources(EDF
        PRIVATE
        src/Platform/AssertZephyr.cpp
    )
else()
    target_sources(EDF
        PRIVATE
        src/Platform/AssertStandard.cpp
    )
endif()

edf_apply_common_settings(EDF)

list(APPEND EDF_EXPORTED_TARGETS EDF)

# -----------------------------------------------------------------------------
# Peripherals Library (Depends on EDF)
# -----------------------------------------------------------------------------
if(EDF_BUILD_PERIPHERALS)
    add_library(Peripherals INTERFACE)

    set_target_properties(Peripherals PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    target_include_directories(Peripherals
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

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
# Installation & Packaging (Only active when EDF is built as a top-level project)
# -----------------------------------------------------------------------------
if(NOT DEFINED ZEPHYR_BASE)
    if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        include(GNUInstallDirs)

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
    endif()

    if(EDF_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if(EDF_BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()