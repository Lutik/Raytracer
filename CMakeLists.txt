cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(Raytracer CXX)

include_directories(src)

set(SOURCES
    src/main.cpp
    src/sdl_wrappers.cpp
    src/sdl_wrappers.h
    src/RT/Types.h
    src/RT/Array2D.h
    src/RT/Math.h
    src/RT/Math.cpp
    src/RT/Shape.h
    src/RT/Material.h
    src/RT/Scene.h
    src/RT/Scene.cpp
    src/RT/Camera.h
    src/RT/Camera.cpp
    src/RT/Raytracer.h
    src/RT/Raytracer.cpp

# Shapes
    src/RT/Shapes/Sphere.h
    src/RT/Shapes/Sphere.cpp

# Materials
    src/RT/Materials/Diffuse.h
    src/RT/Materials/Diffuse.cpp
    src/RT/Materials/Light.h
    src/RT/Materials/Light.cpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(Raytracer WIN32 ${SOURCES})

set_target_properties(Raytracer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Raytracer)

find_package(SDL2 REQUIRED)
target_link_libraries(Raytracer PRIVATE SDL2::SDL2 SDL2::SDL2main)