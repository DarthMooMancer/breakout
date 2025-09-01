cmake_minimum_required(VERSION 3.16)
project(breakout)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
include_directories(include)

set(SOURCES
	src/main.cpp
	# src/input.cpp
	# src/window.cpp
	# src/elements.cpp
)

add_executable(breakout ${SOURCES})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(breakout ${CURSES_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
