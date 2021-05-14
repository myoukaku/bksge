add_executable(sample_render_logic_op sample_render_logic_op_main.cpp)
set_target_properties(sample_render_logic_op PROPERTIES FOLDER "samples")
target_link_libraries(sample_render_logic_op PRIVATE bksge)
