cmake_minimum_required(VERSION 3.21)
project( prcv2)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(arSystem arSystem.cpp processors.cpp)
add_executable(harrisCorner harrisCorner.cpp processors.cpp)

# link dynamic libraries to this executable
target_link_libraries(arSystem ${OpenCV_LIBS})
target_link_libraries(harrisCorner ${OpenCV_LIBS})