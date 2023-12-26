
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_sources( ${EXE_NAME}  PUBLIC example/mesh/em_main.cpp )
else()
  target_sources( ${EXE_NAME}  PUBLIC example/mesh/main.cpp )
endif()

target_sources(${EXE_NAME} PUBLIC 
  example/mesh/mesh.h 
  example/mesh/mesh.cpp
  )
