set(TARGET_NAME "sample_open_type_font")

add_executable(${TARGET_NAME} sample_open_type_font_main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "samples")
target_link_libraries(${TARGET_NAME} bksge)

#set(ASSETS_DIR "${PROJECT_SOURCE_DIR}/assets")
#set(ASSETS
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-Black.otf"
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-Bold.otf"
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-DemiLight.otf"
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-Light.otf"
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-Medium.otf"
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-Regular.otf"
#	"${ASSETS_DIR}/fonts/NotoSansCJKjp-Thin.otf"
#	"${ASSETS_DIR}/fonts/NotoSansMonoCJKjp-Bold.otf"
#	"${ASSETS_DIR}/fonts/NotoSansMonoCJKjp-Regular.otf")
#add_custom_command(
#	TARGET ${TARGET_NAME} POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy
#			${ASSETS}
#			$<TARGET_FILE_DIR:${TARGET_NAME}>)
