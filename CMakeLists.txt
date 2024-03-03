cmake_minimum_required(VERSION 3.16.3)

project( "EDF"
         VERSION 1.0.0
         DESCRIPTION "Embedded Development Framework"
         HOMEPAGE_URL "https://github.com/Veazus/edf"
         LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_LTO
    -flto
)

# Common compile flags
set(CMAKE_CXX_FLAGS_COMMON
    # Optimization level
    -Os
    -g0

    # Warning flags
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wundef
    -Wconversion

    # MISC flags
    -fno-common
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -fno-unwind-tables
    -fno-rtti
    -fno-threadsafe-statics
    ${CMAKE_CXX_LTO}
)

# Common link flags
set(CMAKE_LINKER_FLAGS_COMMON
    -Wl,--gc-sections
    # -Wl,--print-gc-sections
    ${CMAKE_CXX_LTO}
)

# include(GNUInstallDirs)

add_library( EDF STATIC )

target_compile_features( EDF PUBLIC cxx_std_17 )

target_include_directories( EDF
                            PUBLIC
                            "include"
)

target_sources( EDF
                PRIVATE
                "src/String.cpp"
)

target_compile_options( EDF PRIVATE ${CMAKE_CXX_FLAGS_COMMON} )
target_link_options( EDF PRIVATE ${CMAKE_EXE_LINKER_FLAGS_COMMON} )

# # For now, add all of the others. Eventually it would be nice to be able to configure the project to have Peripherals, Drivers, and/or MCU
add_library( Peripherals INTERFACE )

target_compile_features( Peripherals INTERFACE cxx_std_17 )

target_include_directories( Peripherals
                            INTERFACE
                            "include"
                            "include/EDF/src"
)
# add_subdirectory(EDF/Drivers)
# # For now, no specific MCU configuration is selected.
# add_subdirectory(EDF/MCU)

# install( FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/EDF )


add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)