cmake_minimum_required(VERSION 3.5)

# prevent in-source builds
if (CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
    message(FATAL_ERROR "In source builds are not allowed.")
endif()

# set up some system wide settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(source)

# build unit tests
enable_testing()
add_subdirectory(unit_tests)

