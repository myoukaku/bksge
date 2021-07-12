cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME_BASE ranges)

set(TARGET_NAME bksge_${TARGET_NAME_BASE}_test)
set(TARGET_ALIAS_NAME Bksge::${TARGET_NAME_BASE}_test)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)

target_sources(${TARGET_NAME} INTERFACE ${test_sources})

target_include_directories(${TARGET_NAME} INTERFACE src)

target_link_libraries(${TARGET_NAME} INTERFACE Bksge::${TARGET_NAME_BASE})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../array ${CMAKE_CURRENT_BINARY_DIR}/array)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../deque ${CMAKE_CURRENT_BINARY_DIR}/deque)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../forward_list ${CMAKE_CURRENT_BINARY_DIR}/forward_list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../list ${CMAKE_CURRENT_BINARY_DIR}/list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../set ${CMAKE_CURRENT_BINARY_DIR}/set)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../string ${CMAKE_CURRENT_BINARY_DIR}/string)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../string_view ${CMAKE_CURRENT_BINARY_DIR}/string_view)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../span ${CMAKE_CURRENT_BINARY_DIR}/span)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../unordered_set ${CMAKE_CURRENT_BINARY_DIR}/unordered_set)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../vector ${CMAKE_CURRENT_BINARY_DIR}/vector)

target_link_libraries(${TARGET_NAME}
	INTERFACE
		Bksge::array
		Bksge::deque
		Bksge::forward_list
		Bksge::list
		Bksge::set
		Bksge::string
		Bksge::string_view
		Bksge::span
		Bksge::unordered_set
		Bksge::vector)
