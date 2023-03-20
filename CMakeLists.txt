cmake_minimum_required(VERSION 3.21)
project( prcv2)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(augmentation augmentation.cpp functions.cpp)
add_executable(harrisC harrisC.cpp)

# link dynamic libraries to this executable
target_link_libraries(augmentation ${OpenCV_LIBS})
target_link_libraries(harrisC ${OpenCV_LIBS})