cmake_minimum_required(VERSION 3.0.0)
project(Fractal VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glfw/include)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/glew/lib)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/glfw/src)

add_library(Fractal)
add_subdirectory(Source)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set_target_properties(Fractal PROPERTIES LINK_FLAGS "-O0 -o testme.html -s USE_GLFW=3 ")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(Fractal libglfw3.a)
target_link_libraries(Fractal libGLEW.a)
target_link_libraries(Fractal libGLU.so)
target_link_libraries(Fractal libGL.so)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
