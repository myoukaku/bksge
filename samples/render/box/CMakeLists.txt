add_executable(sample_render_box sample_render_box_main.cpp)
set_target_properties(sample_render_box PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_box PRIVATE bksge)
