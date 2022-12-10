add_executable(Fractal 
    main.cpp
    Fractal.cpp
    Gui.cpp
    Renderer.cpp
    Texture.cpp
    targa.cpp
    )

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set_target_properties(Fractal PROPERTIES LINK_FLAGS "-o testme.html -s USE_GLFW=3 --preload-file file.txt --preload-file test.tga --preload-file test3.tga")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(Fractal libglfw3.a)
target_link_libraries(Fractal libGLEW.a)
target_link_libraries(Fractal libGLU.so)
target_link_libraries(Fractal libGL.so)
