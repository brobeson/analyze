cmake_minimum_required(VERSION 3.5)

# prevent in-source builds
if (CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
    message(FATAL_ERROR "In source builds are not allowed.")
endif()

#------------------------------------------------------------------------------
#                                                         system wide settings
#------------------------------------------------------------------------------
project(analyze VERSION 0.0.0)

# set up only debug and release builds. this is for multi-configuration build systems, like Visual
# Studio, and single configuration build systems, like make.
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "release" CACHE STRING "Choose the type of build: debug or release." FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 REQUIRED COMPONENTS Core Test)

#------------------------------------------------------------------------------
#                                                    add the software to build
#------------------------------------------------------------------------------
add_subdirectory(source)
include(CTest)
add_subdirectory(unit_tests)

#------------------------------------------------------------------------------
#                                                Doxygen source code reference
#------------------------------------------------------------------------------
#configure_file(doxyfile doxyfile)
#add_custom_target(reference doxygen COMMENT "Generating Doxygen reference manual...")

#------------------------------------------------------------------------------
#                                                     Cppcheck static analysis
#------------------------------------------------------------------------------
#option(cppcheck_config_check
#    "Toggle using the --check-config flag for Cppcheck. Enable this if the Cppcheck output recommends it."
#    off)
#if (cppcheck_config_check)
#    set(check_config "--check-config")
#else()
#    unset(check_config)
#endif()
#add_custom_target(cppcheck
#    cppcheck ${check_config} --inline-suppr --enable=all --quiet ./
#    COMMENT "Running Cppcheck static analysis..."
#    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#------------------------------------------------------------------------------
#                                        lizard cyclomatic complexity analysis
#------------------------------------------------------------------------------
#execute_process(COMMAND nproc OUTPUT_VARIABLE nproc)
#math(EXPR nproc "${nproc} - 1")
#add_custom_target(lizard
#    lizard --ignore_warnings=100000 --working_threads=${nproc} --CCN=10 --warnings_only --modified ./
#    COMMENT "Running lizard cyclomatic complexity analysis..."
#    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

