cmake_minimum_required(VERSION 3.16)
project(Motion2D)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

add_executable(Motion2D main.cpp cleanup.h logSDLError.cpp logSDLError.h texture.cpp texture.h)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(Motion2D ${SDL2_LIBRARIES})

file(COPY resources/ DESTINATION resources)
