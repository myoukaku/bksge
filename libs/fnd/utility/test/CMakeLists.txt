cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME "utility_test")

add_library(${TARGET_NAME} INTERFACE)
add_library(Bksge::${TARGET_NAME} ALIAS ${TARGET_NAME})

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)

target_sources(${TARGET_NAME} INTERFACE ${test_sources})

if(BKSGE_UNITY_BUILD)
  set_target_properties(${TARGET_NAME} PROPERTIES UNITY_BUILD ON)
endif()

target_include_directories(${TARGET_NAME} INTERFACE src)

target_link_libraries(${TARGET_NAME} INTERFACE Bksge::utility)
