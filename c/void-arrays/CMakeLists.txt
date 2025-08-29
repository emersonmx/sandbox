cmake_minimum_required(VERSION 4.0)

project(
    void-arrays
    VERSION 0.1.0
    LANGUAGES C)

set(CMAKE_C_STANDARD 23)

add_executable(void-arrays)
target_sources(void-arrays PRIVATE main.c array.c)
