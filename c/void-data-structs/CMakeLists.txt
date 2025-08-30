cmake_minimum_required(VERSION 4.0)

project(
    void-data-structs
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
    unity
    URL https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.1.tar.gz
    URL_HASH SHA256=b41a66d45a6b99758fb3202ace6178177014d52fc524bf1f72687d93e9867292
)
FetchContent_MakeAvailable(unity)

include(CTest)

add_executable(array_test)
target_sources(array_test PRIVATE array_test.c array.c)
target_include_directories(array_test PRIVATE ${unity_SOURCE_DIR}/src)
target_link_libraries(array_test unity)
add_test(array_test array_test)

add_executable(stack_test)
target_sources(stack_test PRIVATE stack_test.c stack.c)
target_include_directories(stack_test PRIVATE ${unity_SOURCE_DIR}/src)
target_link_libraries(stack_test unity)
add_test(stack_test stack_test)

add_executable(deque_test)
target_sources(deque_test PRIVATE deque_test.c deque.c)
target_include_directories(deque_test PRIVATE ${unity_SOURCE_DIR}/src)
target_link_libraries(deque_test unity)
add_test(deque_test deque_test)
