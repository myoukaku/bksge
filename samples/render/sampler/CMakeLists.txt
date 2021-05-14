add_executable(sample_render_sampler sample_render_sampler_main.cpp)
set_target_properties(sample_render_sampler PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_sampler PRIVATE bksge)
