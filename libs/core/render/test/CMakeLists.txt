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

option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../../externals/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

target_link_libraries(${TARGET_NAME}
	PRIVATE
		Bksge::render
		GTest::gtest
		GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
