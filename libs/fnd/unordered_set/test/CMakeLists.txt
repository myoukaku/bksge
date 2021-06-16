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

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master)
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
FetchContent_MakeAvailable(googletest)

target_link_libraries(${TARGET_NAME}
	PRIVATE
		Bksge::unordered_set
		GTest::gtest
		GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
