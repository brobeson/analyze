project(analyze)
configure_file(version.in.h version.h)
add_executable(${PROJECT_NAME}
    bounding_box.h
    comma_ctype.h
    iou.cpp
    iou.h
    main.cpp
    version.in.h
    )
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
