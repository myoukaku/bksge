add_executable(sample_input_mouse sample_input_mouse_main.cpp)
set_target_properties(sample_input_mouse PROPERTIES FOLDER "samples")
target_link_libraries(sample_input_mouse PRIVATE bksge)
