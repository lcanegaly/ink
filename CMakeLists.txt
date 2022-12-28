cmake_minimum_required(VERSION 3.0.0)
project(Fractal VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glfw/include)
#include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glew/include)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/glew/lib)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/glfw/src)

add_subdirectory(Source)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
