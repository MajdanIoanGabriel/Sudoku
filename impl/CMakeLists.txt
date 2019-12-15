cmake_minimum_required(VERSION 3.5.1)  
project(sudoku)               
set(CMAKE_CXX_STANDARD 14)            

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES src/main.cpp src/Grid.cpp src/GameWindow.cpp src/MainWindow.cpp src/GameWindow.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)