project(unit_tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit_tests")
set(CMAKE_AUTOMOC on)
set(CMAKE_INCLUDE_CURRENT_DIR on)
find_package(Qt5Test)

#-------------------------------------------------------------------------------
#                                             unit tests analyzer::bounding_box
#-------------------------------------------------------------------------------
set(test_name "bounding-box-test")
add_executable(${test_name} bounding_box_test.cpp)
target_link_libraries(${test_name} Qt5::Test)
target_include_directories(${test_name}
    PRIVATE ${CMAKE_SOURCE_DIR}/source ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME ${test_name} COMMAND ${test_name})

