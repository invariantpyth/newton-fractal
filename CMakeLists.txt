cmake_minimum_required(VERSION 3.22)
project(newton_fractal)

set(OpenCV_DIR "./OpenCV/build")
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_STANDARD 14)

add_executable(newton_fractal "main.cpp")
target_link_libraries( newton_fractal ${OpenCV_LIBS} )