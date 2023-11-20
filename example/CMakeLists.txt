if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_sources( ${PROJECT_NAME} PUBLIC example/em_main.cpp )
else()
  target_sources( ${PROJECT_NAME} PUBLIC example/main.cpp )
endif()

target_sources(${PROJECT_NAME} PUBLIC 
  example/merge.h 
  example/merge.cpp
  )
