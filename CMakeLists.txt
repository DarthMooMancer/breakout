cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(breakout)
include_directories(include)

set(SOURCES
	src/main.cpp
	src/input.cpp
	src/window.cpp
	src/engine.cpp
)

add_executable(breakout ${SOURCES})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(breakout ${CURSES_LIBRARIES})
