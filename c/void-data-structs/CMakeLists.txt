cmake_minimum_required(VERSION 4.0)

project(
    void-data-structs
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)

add_executable(void-data-structs)
target_sources(void-data-structs PRIVATE main.c array.c)
