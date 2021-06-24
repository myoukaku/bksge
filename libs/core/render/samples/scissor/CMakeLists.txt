set(TARGET_NAME "sample_render_scissor")

add_executable(${TARGET_NAME} sample_render_scissor_main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "samples")
target_link_libraries(${TARGET_NAME} PRIVATE Bksge::render)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../input ${CMAKE_CURRENT_BINARY_DIR}/input)
target_link_libraries(${TARGET_NAME} PRIVATE Bksge::input)
