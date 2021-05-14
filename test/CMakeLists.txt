
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

add_subdirectory(googletest)
set_target_properties(gtest      PROPERTIES FOLDER "externals")
#set_target_properties(gtest_main PROPERTIES FOLDER "externals")
#set_target_properties(gmock      PROPERTIES FOLDER "externals")
#set_target_properties(gmock_main PROPERTIES FOLDER "externals")

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)
add_executable(unit_test ${test_sources} src/main.cpp)
if(BKSGE_UNITY_BUILD)
  set_target_properties(unit_test PROPERTIES UNITY_BUILD ON)
endif()

target_include_directories(unit_test PRIVATE src)

target_link_libraries(unit_test PRIVATE bksge gtest)

include(GoogleTest)
gtest_discover_tests(unit_test)
