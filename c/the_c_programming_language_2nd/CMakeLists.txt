cmake_minimum_required(VERSION 3.14...3.25)

project(
  tcpl2nd
  VERSION 0.1
  DESCRIPTION "Codes from the book 'The C programming language - 2nd edition'"
  LANGUAGES C)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED ON)

    # Optionally set things like CMAKE_C_STANDARD,
    # CMAKE_POSITION_INDEPENDENT_CODE here

    # Let's ensure -std=cxx instead of -std=gxx
    set(CMAKE_C_EXTENSIONS OFF)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
