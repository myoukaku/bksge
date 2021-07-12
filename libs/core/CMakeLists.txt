cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME_BASE core)

set(TARGET_NAME bksge_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Bksge::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

set(SUBDIRECTORIES
	font
	input
	math
	render
	window)

foreach(SUBDIRECTORY ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIRECTORY})
	target_link_libraries(${TARGET_NAME} INTERFACE Bksge::${SUBDIRECTORY})
endforeach()

set(TEST_TARGET_NAME ${TARGET_NAME}_test)
set(TEST_TARGET_ALIAS_NAME ${TARGET_ALIAS_NAME}_test)

add_library(${TEST_TARGET_NAME} INTERFACE)
add_library(${TEST_TARGET_ALIAS_NAME} ALIAS ${TEST_TARGET_NAME})
foreach(SUBDIRECTORY ${SUBDIRECTORIES})
	target_link_libraries(${TEST_TARGET_NAME} INTERFACE Bksge::${SUBDIRECTORY}_test)
endforeach()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  if(BKSGE_BUILD_TESTING)
    enable_testing()
    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../externals/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
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
