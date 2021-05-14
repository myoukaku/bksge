add_executable(sample_input_keyboard sample_input_keyboard_main.cpp)
set_target_properties(sample_input_keyboard PROPERTIES FOLDER "samples")
target_link_libraries(sample_input_keyboard PRIVATE bksge)
