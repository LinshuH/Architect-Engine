cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(MainEngine)
SET(VTK_DIR ~/programs/VTK-6.3.0/)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})



add_executable(MainEngine MainEngine DrawObject.h DrawObject.cxx )

if(VTK_LIBRARIES)
  target_link_libraries(MainEngine ${VTK_LIBRARIES})
else()
  target_link_libraries(MainEngine vtkHybrid)
endif()

