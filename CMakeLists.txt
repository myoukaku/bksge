cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME bksge)
set(TARGET_ALIAS_NAME Bksge::${TARGET_NAME_BASE})

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} STATIC)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES USE_FOLDERS ON)

option(BKSGE_UNITY_BUILD "Use Unity Builds" OFF)
option(BKSGE_BUILD_TESTING "Build tests" ON)
option(BKSGE_BUILD_SAMPLES "Build samples" ON)
option(BKSGE_COVERAGE "Coverage" OFF)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (BKSGE_COVERAGE)
  target_compile_options(${TARGET_NAME} PRIVATE --coverage)
endif()

if(BKSGE_UNITY_BUILD)
  set_target_properties(${TARGET_NAME} PROPERTIES UNITY_BUILD ON)
endif()

add_subdirectory(libs)
target_link_libraries(${TARGET_NAME} PUBLIC Bksge::fnd)
target_link_libraries(${TARGET_NAME} PUBLIC Bksge::core)

set(TEST_TARGET_NAME ${TARGET_NAME}_test)
set(TEST_TARGET_ALIAS_NAME ${TARGET_ALIAS_NAME}_test)

add_library(${TEST_TARGET_NAME} INTERFACE)
add_library(${TEST_TARGET_ALIAS_NAME} ALIAS ${TEST_TARGET_NAME})

target_link_libraries(${TEST_TARGET_NAME} INTERFACE Bksge::fnd_test)
target_link_libraries(${TEST_TARGET_NAME} INTERFACE Bksge::core_test)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  if(BKSGE_BUILD_TESTING)
    enable_testing()
    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
	add_executable(unit_test)
	target_link_libraries(unit_test
	  PRIVATE
		${TEST_TARGET_NAME}
		GTest::gtest
		GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_test)
  endif()
endif()
