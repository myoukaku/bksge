add_executable(sample_render_texture sample_render_texture_main.cpp)
set_target_properties(sample_render_texture PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_texture PRIVATE bksge)
