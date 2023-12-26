
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_sources( ${EXE_NAME}  PUBLIC example/canvas/em_main.cpp )
else()
  target_sources( ${EXE_NAME}  PUBLIC example/canvas/main.cpp )
endif()

target_sources(${EXE_NAME} PUBLIC 
  example/canvas/mesh.h 
  example/canvas/mesh.cpp
  )
