add_executable(sample_render_triangle sample_render_triangle_main.cpp)
set_target_properties(sample_render_triangle PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_triangle PRIVATE bksge)
