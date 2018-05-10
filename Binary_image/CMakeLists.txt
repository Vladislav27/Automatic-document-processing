cmake_minimum_required(VERSION 3.8)
project(Binary_image)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp ImageBinarization.cpp ImageBinarization.h)
add_executable(Binary_image ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( Binary_image ${OpenCV_LIBS} )