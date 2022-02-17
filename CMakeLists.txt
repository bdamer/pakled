cmake_minimum_required(VERSION 2.8)
project(pakled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Libraries
find_package(SDL2 REQUIRED)
# FIXME
set(SDL2_IMAGE_LIBRARIES /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
#find_package(SDL2_Image REQUIRED)
set(DUKAT_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../dukat/lib/libdukat.a)

find_package(GLEW REQUIRED)
# Set OpenGL preference
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_package(PNG REQUIRED)

# The following folders will be included
add_subdirectory(src)
