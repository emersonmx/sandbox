cmake_minimum_required(VERSION 4.0)

project(
    hello-libuv
    VERSION 0.1.0
    LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(BUILD_TESTING False)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -fsanitize=address")
endif()

include(FetchContent)
FetchContent_Declare(
  libuv
  URL https://github.com/libuv/libuv/archive/refs/tags/v1.51.0.tar.gz
  URL_HASH SHA256=27e55cf7083913bfb6826ca78cde9de7647cded648d35f24163f2d31bb9f51cd
)
FetchContent_MakeAvailable(libuv)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE libuv::libuv)
