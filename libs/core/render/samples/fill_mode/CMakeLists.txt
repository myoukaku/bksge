﻿set(TARGET_NAME "sample_render_fill_mode")

add_executable(${TARGET_NAME} sample_render_fill_mode_main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "samples")
target_link_libraries(${TARGET_NAME} PRIVATE Bksge::render)
