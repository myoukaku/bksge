add_executable(sample_render_point sample_render_point_main.cpp)
set_target_properties(sample_render_point PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_point PRIVATE bksge)
