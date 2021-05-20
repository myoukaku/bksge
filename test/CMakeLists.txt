add_executable(unit_test)

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)
target_sources(unit_test PRIVATE ${test_sources} src/main.cpp)

if(BKSGE_UNITY_BUILD)
  set_target_properties(unit_test PROPERTIES UNITY_BUILD ON)
endif()

target_include_directories(unit_test PRIVATE src)

target_link_libraries(unit_test PRIVATE bksge GTest::gtest)

include(GoogleTest)
gtest_discover_tests(unit_test)
