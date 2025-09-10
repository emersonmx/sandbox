cmake_minimum_required(VERSION 4.0)

project(
    simple-server-libuv
    VERSION 0.1.0
    LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  libuv
  URL https://github.com/libuv/libuv/archive/refs/tags/v1.51.0.tar.gz
  URL_HASH SHA256=27e55cf7083913bfb6826ca78cde9de7647cded648d35f24163f2d31bb9f51cd
)
FetchContent_MakeAvailable(libuv)

add_executable(simple-server-libuv)
target_sources(simple-server-libuv PRIVATE main.c)
target_link_libraries(simple-server-libuv PRIVATE libuv::libuv)
