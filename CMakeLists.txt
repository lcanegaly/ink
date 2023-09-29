set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  # We are building as stand-alone project
  cmake_minimum_required(VERSION 3.11.0)
  project(ink VERSION 0.0.1)
  set(BUILD_DEMO "TRUE")
else()
  set(BUILD_DEMO "FALSE")
endif()

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/miniaudio)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/build/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/build/Debug)

add_executable(${PROJECT_NAME})
add_subdirectory(src)

if (BUILD_DEMO MATCHES "TRUE")
  add_subdirectory(example)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(${PROJECT_NAME} glfw3)
  target_link_libraries(${PROJECT_NAME} glew32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(${PROJECT_NAME} OpenGL::GL)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(${PROJECT_NAME} libglfw3.a)
  target_link_libraries(${PROJECT_NAME} libGLEW.so)
  target_link_libraries(${PROJECT_NAME} libGL.so)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set_target_properties(${PROJECT_NAME}PROPERTIES LINK_FLAGS 
    "-O3 -o out.html --shell-file shell_minimal.html -s USE_GLFW=3 \
    --preload-file assets/test.tga")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
