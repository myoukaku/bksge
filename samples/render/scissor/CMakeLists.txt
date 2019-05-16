cmake_minimum_required(VERSION 3.12)

include(${PROJECT_SOURCE_DIR}/cmake/assign_source_group.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sample_render_scissor sample_render_scissor_main.cpp)
assign_source_group(sample_render_scissor.cpp)
set_target_properties(sample_render_scissor PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_scissor bksge)
