cmake_minimum_required(VERSION 3.16.3)

project( "EDF"
         VERSION 1.0.0
         DESCRIPTION "Embedded Development Framework"
         HOMEPAGE_URL "https://github.com/Veazus/edf"
         LANGUAGES C CXX
)

# include(GNUInstallDirs)

add_library( EDF INTERFACE )

target_compile_features( EDF INTERFACE cxx_std_17 )

target_include_directories( EDF
                            INTERFACE
                            "include"
)

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