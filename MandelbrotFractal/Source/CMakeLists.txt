

add_executable(Fractal 
    main.cpp
    Fractal.cpp
    Gui.cpp
    Renderer.cpp
    Texture.cpp
    )

  #add_executable(Fractal hello_gl.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(Fractal libglfw3.a)
target_link_libraries(Fractal libGLEW.a)
target_link_libraries(Fractal libGLU.so)
target_link_libraries(Fractal libGL.so)
