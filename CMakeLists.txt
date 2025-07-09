cmake_minimum_required(VERSION 3.30)
project(ascii-convert LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_package(Python3 COMPONENTS Development REQUIRED)

add_library(ascii_convert SHARED ${SOURCES})

target_link_libraries(ascii_convert PRIVATE SFML::Graphics Python3::Python Python3::Module)

set_target_properties(
    ascii_convert
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "ascii_convert"
        LINKER_LANGUAGE CXX
    )