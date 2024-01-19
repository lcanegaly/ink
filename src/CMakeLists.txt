message(DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(${LIB_NAME} PRIVATE 
 ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/targa/targa.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/image_view.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/button.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/audio.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/mesh_renderer.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/objimp/obj.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/physics/collider.cpp
)




