add_executable(sample_render_line sample_render_line_main.cpp)
set_target_properties(sample_render_line PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_line PRIVATE bksge)
