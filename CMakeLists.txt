cmake_minimum_required(VERSION 3.10)

project(c_http VERSION 1.0)

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
