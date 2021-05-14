add_executable(sample_render_clear sample_render_clear_main.cpp)
set_target_properties(sample_render_clear PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_clear PRIVATE bksge)
