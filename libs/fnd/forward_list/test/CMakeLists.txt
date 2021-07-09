cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME_BASE forward_list)

set(TARGET_NAME bksge_${TARGET_NAME_BASE}_test)
set(TARGET_ALIAS_NAME Bksge::${TARGET_NAME_BASE}_test)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)

target_sources(${TARGET_NAME} INTERFACE ${test_sources})

if(BKSGE_UNITY_BUILD)
  set_target_properties(${TARGET_NAME} PROPERTIES UNITY_BUILD ON)
endif()

target_include_directories(${TARGET_NAME} INTERFACE src)

target_link_libraries(${TARGET_NAME} INTERFACE Bksge::${TARGET_NAME_BASE})
