add_executable(sample_render_indexed sample_render_indexed_main.cpp)
set_target_properties(sample_render_indexed PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_indexed PRIVATE bksge)
