add_executable(sample_window_window sample_window_window_main.cpp)
set_target_properties(sample_window_window PROPERTIES FOLDER "samples")
target_link_libraries(sample_window_window PRIVATE bksge)
