cmake_minimum_required(VERSION 3.1.0)

project(CMake_build_Qt_Demo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(CMake_build_Qt_Demo
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

target_link_libraries(CMake_build_Qt_Demo Qt5::Widgets)