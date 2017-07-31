# Qt Test version 5 is required for building the unit tests
find_package(Qt5Test)
if (NOT Qt5Test_FOUND)
    message(STATUS "Qt5 Test module wasn't found. I'm skipping the unit tests and code coverage.")
    return()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/unit_tests")
set(CMAKE_AUTOMOC on)

#------------------------------------------------------------------------------
#                                               unit test code coverage report
#------------------------------------------------------------------------------
if (unit_test_coverage)
    # determine the git branch, for use in the report title
    execute_process(COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE branch)
    string(STRIP "${branch}" branch)

    # set up coverage information files
    set(baseline "baseline.info")
    set(tracefile "coverage.info")

    # the build target for generating unit test coverage
    add_custom_target(coverage
        COMMAND lcov --directory ${CMAKE_BINARY_DIR}
                     --zerocounters
        COMMAND lcov --directory ${CMAKE_BINARY_DIR}
                     --base-directory ${CMAKE_SOURCE_DIR}
                     --capture
                     --initial
                     --output-file ${baseline}
        COMMAND ctest --parallel=${nproc}
        COMMAND lcov --directory ${CMAKE_BINARY_DIR}
                     --capture
                     --output-file ${tracefile}
        COMMAND lcov --add-tracefile ${baseline}
                     --add-tracefile ${tracefile}
                     --output-file ${tracefile}
        COMMAND lcov --remove ${tracefile} '/usr/*'
                     --output-file ${tracefile}
        COMMAND genhtml --legend
                        --demangle-cpp
                        --title "${PROJECT_NAME} ${branch}"
                        --output-directory ${CMAKE_BINARY_DIR}/coverage
                        ${tracefile}
        COMMENT "Running unit tests..."
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
else()
    message(STATUS "unit_test_coverage is off, so the coverage build target won't be available.")
endif()

#-------------------------------------------------------------------------------
#                                             unit tests analyze::bounding_box
#-------------------------------------------------------------------------------
set(test_name "bounding-box-test")
add_executable(${test_name}
    bounding_box_test.cpp
    ${CMAKE_SOURCE_DIR}/source/bounding_box.h)
target_link_libraries(${test_name} Qt5::Test)
target_include_directories(${test_name}
    PRIVATE ${CMAKE_SOURCE_DIR}/source
            ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME ${test_name} COMMAND ${test_name})

#-------------------------------------------------------------------------------
#                                                      unit tests analyze::iou
#-------------------------------------------------------------------------------
set(test_name "iou-test")
add_executable(${test_name}
    iou_test.cpp
    ${CMAKE_SOURCE_DIR}/source/iou.cpp
    ${CMAKE_SOURCE_DIR}/source/iou.h)
target_link_libraries(${test_name} Qt5::Test)
target_include_directories(${test_name}
    PRIVATE ${CMAKE_SOURCE_DIR}/source
            ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME ${test_name} COMMAND ${test_name})
