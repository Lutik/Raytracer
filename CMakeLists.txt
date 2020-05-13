cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(Raytracer CXX)

include_directories(src)
set(SOURCES
    src/main.cpp
    src/sdl_wrappers.cpp
)

add_executable(Raytracer WIN32 ${SOURCES})

set_target_properties(Raytracer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Raytracer)

find_package(SDL2 REQUIRED)
target_link_libraries(Raytracer PRIVATE SDL2::SDL2 SDL2::SDL2main)