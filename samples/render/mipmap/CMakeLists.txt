add_executable(sample_render_mipmap sample_render_mipmap_main.cpp)
set_target_properties(sample_render_mipmap PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_mipmap PRIVATE bksge)
