add_executable(Fractal 
    main.cpp
    fractal.cpp
    renderer.cpp
    targa/targa.cpp
    object.cpp
    image.cpp
    window.cpp
    application.cpp
    input.cpp
    button.cpp
    sprite.cpp
    textbox.cpp
    )

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set_target_properties(Fractal PROPERTIES LINK_FLAGS "-O0 -o testme.html -s USE_GLFW=3 --preload-file right.tga --preload-file left.tga --preload-file down.tga --preload-file up.tga --preload-file minus.tga --preload-file plus.tga --preload-file font1.tga")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(Fractal libglfw3.a)
target_link_libraries(Fractal libGLEW.a)
target_link_libraries(Fractal libGLU.so)
target_link_libraries(Fractal libGL.so)
