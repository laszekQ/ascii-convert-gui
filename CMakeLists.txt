cmake_minimum_required(VERSION 3.30)
project(ascii-convert)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
FetchContent_Declare(
sfml
GIT_REPOSITORY https://github.com/SFML/SFML.git
GIT_TAG 3.0.0
)

FetchContent_MakeAvailable(sfml)

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)

add_executable(ascii-convert ${SOURCES})
target_link_libraries(ascii-convert PRIVATE SFML::Graphics)

