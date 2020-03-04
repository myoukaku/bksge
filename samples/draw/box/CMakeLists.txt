cmake_minimum_required(VERSION 3.12)

include(${PROJECT_SOURCE_DIR}/cmake/assign_source_group.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sample_draw_box sample_draw_box_main.cpp)
assign_source_group(sample_draw_box.cpp)
set_target_properties(sample_draw_box PROPERTIES FOLDER "samples")
target_link_libraries(sample_draw_box bksge)
