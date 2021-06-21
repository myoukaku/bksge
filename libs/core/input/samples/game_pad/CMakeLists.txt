set(TARGET_NAME "sample_input_game_pad")

add_executable(${TARGET_NAME} sample_input_game_pad_main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "samples")
target_link_libraries(${TARGET_NAME} Bksge::input)
