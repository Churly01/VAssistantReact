cmake_minimum_required(VERSION 3.22.1)
project( main )
find_package( OpenCV REQUIRED )
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)
include_directories(${LIBCAMERA_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})

add_executable(main main.cpp)
target_link_libraries( main -llccv ${OpenCV_LIBS} )
