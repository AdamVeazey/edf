cmake_minimum_required(VERSION 3.16.3)

project( "EDF"
         VERSION 1.0.0
         DESCRIPTION "Embedded Development Framework"
         HOMEPAGE_URL "https://github.com/Veazus/edf"
         LANGUAGES C CXX
)

# include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)