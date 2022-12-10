cmake_minimum_required(VERSION 3.16)
project (vtkHomework)

find_package (VTK REQUIRED)
include (${VTK_USE_FILE})

add_executable (vtkHomework vtkHomework.cxx)

target_link_libraries (vtkHomework ${VTK_LIBRARIES})
