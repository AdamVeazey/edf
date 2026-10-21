# if(EDF_BUILD_DRIVERS)
#     add_subdirectory(Drivers)
# endif()

add_subdirectory(EDF)

# add_subdirectory(MCU)

if(EDF_BUILD_PERIPHERALS)
    add_subdirectory(Peripherals)
endif()