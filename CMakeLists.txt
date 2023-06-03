cmake_minimum_required(VERSION 3.11.0)
project(ink VERSION 0.0.1)

set(BUILD_DEMO "FALSE")

include(CTest)
enable_testing()

#include_directories(${PROJECT_SOURCE_DIR}/dependencies/glew/include)
link_directories(${PROJECT_SOURCE_DIR}/dependencies/glew/lib)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/miniaudio)
link_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/build/src)
link_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/build/Debug)

add_executable(ink)
add_subdirectory(src)
if (BUILD_DEMO MATCHES "TRUE")
  add_subdirectory(example)
elseif (BUILD_DEMO MATCHES "FALSE")
  add_subdirectory(client)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(ink glfw3)
  target_link_libraries(ink glew32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(ink OpenGL::GL)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(ink libglfw3.a)
  target_link_libraries(ink libGLEW.so)
  target_link_libraries(ink libGL.so)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set_target_properties(ink PROPERTIES LINK_FLAGS 
    "-O3 -o out.html --shell-file shell_minimal.html -s USE_GLFW=3 --preload-file assets/accumulator.tga \
    --preload-file assets/data.tga --preload-file assets/instruction.tga \
    --preload-file assets/light.tga --preload-file assets/run.tga \
    --preload-file assets/win.tga --preload-file assets/addr.tga \
    --preload-file assets/light_off.tga --preload-file assets/memory.tga \
    --preload-file assets/step.tga --preload-file assets/font1_t.tga \
    --preload-file assets/tube.tga")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
