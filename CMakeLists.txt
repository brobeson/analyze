cmake_minimum_required(VERSION 3.5)

# prevent in-source builds
if (CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
    message(FATAL_ERROR "In source builds are not allowed.")
endif()

#------------------------------------------------------------------------------
#                                                         system wide settings
#------------------------------------------------------------------------------
# require a C++14 compiler
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# enable "all" warnings, enable the extra warnings (which aren't enabled by Wall), treat warnings as
# errors, and be pedantic when it comes to ISO C++ adherence.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#------------------------------------------------------------------------------
#                                                    add the software to build
#------------------------------------------------------------------------------
add_subdirectory(source)
enable_testing()
add_subdirectory(unit_tests)

