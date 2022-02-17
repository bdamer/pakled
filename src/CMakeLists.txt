include_directories(../../dukat/include)

add_executable(pakled stdafx.cpp binentry.cpp packer.cpp pakled.cpp)

target_link_libraries(pakled ${DUKAT_LIBRARY} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} 
    ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${X11_Xext_LIB} ${CMAKE_THREAD_LIBS_INIT})
