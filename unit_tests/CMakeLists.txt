#------------------------------------------------------------------------------
#                                               unit test code coverage report
#------------------------------------------------------------------------------
# provide a CMake time option to turn on and off unit test code coverage
#option(unit_test_coverage
#       "Toggle generating a build target for unit test code coverage."
#       off)
#if (unit_test_coverage)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
#endif()
#
#if (unit_test_coverage)
#    # determine the git branch, for use in the report title
#    execute_process(COMMAND git rev-parse --abbrev-ref HEAD
#        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#        OUTPUT_VARIABLE branch)
#    string(STRIP "${branch}" branch)
#
#    # set up coverage information files
#    set(baseline "baseline.info")
#    set(tracefile "coverage.info")
#
#    # the build target for generating unit test coverage
#    add_custom_target(coverage
#        COMMAND lcov --directory ${CMAKE_BINARY_DIR}
#                     --zerocounters
#        COMMAND lcov --directory ${CMAKE_BINARY_DIR}
#                     --base-directory ${CMAKE_SOURCE_DIR}
#                     --capture
#                     --initial
#                     --output-file ${baseline}
#        COMMAND ctest --parallel=${nproc}
#        COMMAND lcov --directory ${CMAKE_BINARY_DIR}
#                     --capture
#                     --output-file ${tracefile}
#        COMMAND lcov --add-tracefile ${baseline}
#                     --add-tracefile ${tracefile}
#                     --output-file ${tracefile}
#        COMMAND lcov --remove ${tracefile} '/usr/*' '*.moc'
#                     --output-file ${tracefile}
#        COMMAND genhtml --legend
#                        --demangle-cpp
#                        --title "${PROJECT_NAME} ${branch}"
#                        --output-directory ${CMAKE_BINARY_DIR}/coverage
#                        ${tracefile}
#        COMMENT "Running unit tests..."
#        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
#else()
#    message(STATUS "unit_test_coverage is off, so the coverage build target won't be available.")
#endif()

# create an executable for each test, then append the test name to the list of tests
add_executable(bounding-box-test
    bounding_box_test.cpp
    ${analyze_SOURCE_DIR}/bounding_box.h)
list(APPEND tests bounding-box-test)

add_executable(iou-test
    iou_test.cpp 
    ${analyze_SOURCE_DIR}/iou.cpp
    ${analyze_SOURCE_DIR}/iou.h
    )
list(APPEND tests iou-test)

# set various properties common to all the tests
set_target_properties(${tests} PROPERTIES AUTOMOC on)
foreach(test IN LISTS tests)
    target_compile_options(${test} PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        )
    target_link_libraries(${test}
        $<$<CONFIG:Debug>:asan>
        Qt5::Test
        )
    target_include_directories(${test} PRIVATE
        ${analyze_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        )
    add_test(NAME ${test} COMMAND ${test})
endforeach()

