add_executable(sample_render_scissor sample_render_scissor_main.cpp)
set_target_properties(sample_render_scissor PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_scissor PRIVATE bksge)
