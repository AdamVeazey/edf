# set(
#     HEADERS
#     # "Assert.hpp"
#     # "Array.hpp"
# )

# set( SOURCES
#     #  ".cpp"
# )

add_library( EDF INTERFACE )

target_include_directories( EDF
                            INTERFACE
                            ${CMAKE_CURRENT_SOURCE_DIR}
)

# # For now, add all of the others. Eventually it would be nice to be able to configure the project to have Peripherals, Drivers, and/or MCU
# add_subdirectory(EDF/Peripherals)
# add_subdirectory(EDF/Drivers)
# # For now, no specific MCU configuration is selected. 
# add_subdirectory(EDF/MCU)

# install( FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/EDF )
