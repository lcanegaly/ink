cmake_minimum_required(VERSION 3.11.0)
project(physx VERSION 0.0.1)


include_directories(../../dependencies/glm/glm)
include_directories(../../include/)


add_executable(physx)

target_sources(physx PRIVATE 
 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/collider.cpp
 ../objimp/obj.cpp
) 

