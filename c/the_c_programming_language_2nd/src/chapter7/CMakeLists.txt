file(GLOB source_files "*.c")

foreach(source_file ${source_files})
    get_filename_component(executable_name ${source_file} NAME_WE)
    add_executable(${executable_name} ${source_file})
    target_link_libraries(${executable_name} ${MATH_LIB})
endforeach()
