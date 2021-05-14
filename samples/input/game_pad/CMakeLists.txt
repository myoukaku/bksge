add_executable(sample_input_game_pad sample_input_game_pad_main.cpp)
set_target_properties(sample_input_game_pad PROPERTIES FOLDER "samples")
target_link_libraries(sample_input_game_pad PRIVATE bksge)
