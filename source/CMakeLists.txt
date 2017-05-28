find_package(Qt5Core)
add_executable(${PROJECT_NAME}
    bounding_box.h
    comma_ctype.h
    iou.cpp
    iou.h
    main.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
