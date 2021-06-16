cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME "unit_test")

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)

if (TARGET ${TARGET_NAME})
	target_sources(${TARGET_NAME} PRIVATE ${test_sources})
	RETURN()
endif()

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${test_sources})

if(BKSGE_UNITY_BUILD)
  set_target_properties(${TARGET_NAME} PROPERTIES UNITY_BUILD ON)
endif()

target_include_directories(${TARGET_NAME} PRIVATE src)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master)
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
FetchContent_MakeAvailable(googletest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../array ${CMAKE_CURRENT_BINARY_DIR}/array)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../deque ${CMAKE_CURRENT_BINARY_DIR}/deque)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../forward_list ${CMAKE_CURRENT_BINARY_DIR}/forward_list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../list ${CMAKE_CURRENT_BINARY_DIR}/list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../map ${CMAKE_CURRENT_BINARY_DIR}/map)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../set ${CMAKE_CURRENT_BINARY_DIR}/set)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../string ${CMAKE_CURRENT_BINARY_DIR}/string)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../string_view ${CMAKE_CURRENT_BINARY_DIR}/string_view)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../vector ${CMAKE_CURRENT_BINARY_DIR}/vector)

target_link_libraries(${TARGET_NAME}
	PRIVATE
		Bksge::iterator
		Bksge::array
		Bksge::deque
		Bksge::forward_list
		Bksge::list
		Bksge::map
		Bksge::set
		Bksge::string
		Bksge::string_view
		Bksge::vector
		GTest::gtest
		GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
