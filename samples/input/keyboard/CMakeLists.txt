cmake_minimum_required(VERSION 3.12)

include(${PROJECT_SOURCE_DIR}/cmake/assign_source_group.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sample_input_keyboard sample_input_keyboard_main.cpp)
assign_source_group(sample_input_keyboard.cpp)
set_target_properties(sample_input_keyboard PROPERTIES FOLDER "samples")
target_link_libraries(sample_input_keyboard bksge)
