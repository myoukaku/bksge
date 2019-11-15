cmake_minimum_required(VERSION 3.12)

option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(
  PROJ googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  QUIET)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
set_target_properties(gtest      PROPERTIES FOLDER "externals")
set_target_properties(gtest_main PROPERTIES FOLDER "externals")
#set_target_properties(gmock      PROPERTIES FOLDER "externals")
#set_target_properties(gmock_main PROPERTIES FOLDER "externals")

include(${PROJECT_SOURCE_DIR}/cmake/UnityBuild.cmake)

file(GLOB_RECURSE test_sources src/*)
if(BKSGE_UNITY_BUILD)
  ENABLE_UNITY_BUILD(unit_test test_sources 1000 cpp)
endif()
add_executable(unit_test ${test_sources})

include_directories(src)

include(${PROJECT_SOURCE_DIR}/cmake/assign_source_group.cmake)
assign_source_group(${test_sources})

target_link_libraries(unit_test bksge gtest gtest_main)
include_directories(${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(unit_test)
