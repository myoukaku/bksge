add_executable(sample_render_viewport sample_render_viewport_main.cpp)
set_target_properties(sample_render_viewport PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_viewport PRIVATE bksge)
