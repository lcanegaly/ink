if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_sources( ink PUBLIC example/em_main.cpp )
else()
  target_sources( ink PUBLIC example/main.cpp )
endif()

target_sources(ink PUBLIC 
  example/bounce.h 
  example/bounce.cpp
  )
