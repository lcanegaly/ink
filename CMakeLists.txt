cmake_minimum_required(VERSION 3.11.0)
project(ink VERSION 0.0.1)

include(CTest)
enable_testing()

link_directories(${PROJECT_SOURCE_DIR}/dependencies/glew/lib)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glew/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw3/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/miniaudio)
link_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw3/build/src)
link_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw3/build/Debug)

add_executable(ink)
add_subdirectory(src)
add_subdirectory(example)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  #target_link_libraries(ink Ink)
  target_link_libraries(ink glfw3)
  
  #target_sources(ink PUBLIC main.cpp)

  target_link_libraries(ink glew32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(ink OpenGL::GL)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  #target_link_libraries(ink libInk.a)
  target_link_libraries(ink libglfw3.a)
   
  #target_sources(ink PUBLIC main.cpp)

  target_link_libraries(ink libGLEW.so)
  target_link_libraries(ink libGL.so)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_link_libraries(ink libInk.a)
  target_sources(ink PUBLIC emscripten_main.cpp)
 
  set_target_properties(ink PROPERTIES LINK_FLAGS "-O3 -o test.html -s USE_GLFW=3 --preload-file font1.tga")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  
  target_link_libraries(ink libGLEW.so)
  target_link_libraries(ink libGL.so)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
