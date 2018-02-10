cmake_minimum_required(VERSION 3.5)

# prevent in-source builds
if (CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
    message(FATAL_ERROR "In source builds are not allowed.")
endif()

#------------------------------------------------------------------------------
#                                                         system wide settings
#------------------------------------------------------------------------------
# using the VERSION option to the project() function, limits the version to integers. trying to use
# VERSION 2017.07 removes the leading 0 from the month, which I want to remain. so, skip the VERSION
# option to project(), and explicitly set the PROJECT_VERSION variables as strings.
project(analyze)
set(PROJECT_VERSION_MAJOR "2017")
set(PROJECT_VERSION_MINOR "07")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# require a C++14 compiler
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# enable "all" warnings, enable the extra warnings (which aren't enabled by Wall), treat warnings as
# errors, and be pedantic when it comes to ISO C++ adherence.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# provide a CMake time option to turn on and off address sanitizer
option(address_sanitizer
       "Enable address sanitizer for debugging. This should not be enabled for releases."
       off)
if (address_sanitizer)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

# provide a CMake time option to turn on and off unit test code coverage
option(unit_test_coverage
       "Toggle generating a build target for unit test code coverage."
       off)
if (unit_test_coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
endif()

#------------------------------------------------------------------------------
#                                                Doxygen source code reference
#------------------------------------------------------------------------------
configure_file(doxyfile doxyfile)
add_custom_target(reference doxygen COMMENT "Generating Doxygen reference manual...")

#------------------------------------------------------------------------------
#                                                     Cppcheck static analysis
#------------------------------------------------------------------------------
option(cppcheck_config_check
    "Toggle using the --check-config flag for Cppcheck. Enable this if the Cppcheck output recommends it."
    off)
if (cppcheck_config_check)
    set(check_config "--check-config")
else()
    unset(check_config)
endif()

add_custom_target(cppcheck
    cppcheck ${check_config} --inline-suppr --enable=all --quiet ./
    COMMENT "Running Cppcheck static analysis..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#------------------------------------------------------------------------------
#                                        lizard cyclomatic complexity analysis
#------------------------------------------------------------------------------
execute_process(COMMAND nproc OUTPUT_VARIABLE nproc)
math(EXPR nproc "${nproc} - 1")
add_custom_target(lizard
    lizard --ignore_warnings=100000 --working_threads=${nproc} --CCN=10 --warnings_only --modified ./
    COMMENT "Running lizard cyclomatic complexity analysis..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#------------------------------------------------------------------------------
#                                                    add the software to build
#------------------------------------------------------------------------------
add_subdirectory(source)
enable_testing()
#add_subdirectory(unit_tests)

