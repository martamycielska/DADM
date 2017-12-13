
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Visualization2D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Visualization2D MACOSX_BUNDLE Visualization2D.cpp )
 
target_link_libraries(Visualization2D ${VTK_LIBRARIES})
