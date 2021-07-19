cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME_BASE algorithm)

set(TARGET_NAME bksge_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Bksge::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

option(BKSGE_BUILD_TESTING "Build tests" ON)
option(BKSGE_BUILD_SAMPLES "Build samples" ON)
option(BKSGE_COVERAGE "Coverage" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../bit ${CMAKE_CURRENT_BINARY_DIR}/bit)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../concepts ${CMAKE_CURRENT_BINARY_DIR}/concepts)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../config ${CMAKE_CURRENT_BINARY_DIR}/config)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../cstring ${CMAKE_CURRENT_BINARY_DIR}/cstring)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../debug ${CMAKE_CURRENT_BINARY_DIR}/debug)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../functional ${CMAKE_CURRENT_BINARY_DIR}/functional)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../iterator ${CMAKE_CURRENT_BINARY_DIR}/iterator)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../memory ${CMAKE_CURRENT_BINARY_DIR}/memory)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../numeric ${CMAKE_CURRENT_BINARY_DIR}/numeric)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../pair ${CMAKE_CURRENT_BINARY_DIR}/pair)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../random ${CMAKE_CURRENT_BINARY_DIR}/random)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ranges ${CMAKE_CURRENT_BINARY_DIR}/ranges)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../type_traits ${CMAKE_CURRENT_BINARY_DIR}/type_traits)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../vector ${CMAKE_CURRENT_BINARY_DIR}/vector)
target_link_libraries(${TARGET_NAME}
	INTERFACE
		Bksge::bit
		Bksge::concepts
		Bksge::config
		Bksge::cstring
		Bksge::debug
		Bksge::functional
		Bksge::iterator
		Bksge::memory
		Bksge::numeric
		Bksge::pair
		Bksge::random
		Bksge::ranges
		Bksge::type_traits
		Bksge::vector)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMAKE_CXX_FLAGS_* を変更するよりも target_compile_options を使うべきだが、
# /W3 -> /W4 のように既存のオプションを置き換えるには CMAKE_CXX_FLAGS を使うしかない。
# (CMake 3.20 時点)
set(compiler_flags
  CMAKE_CXX_FLAGS
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_MINSIZEREL
  CMAKE_CXX_FLAGS_RELWITHDEBINFO)

foreach(compiler_flag ${compiler_flags})
  if (MSVC)
    # /MD[d] -> /MT[d] (Run-Time Library)
    string(REPLACE "/MD" "/MT" ${compiler_flag} "${${compiler_flag}}")
    
    # /ZI -> /Zi
    string(REPLACE "/ZI" "/Zi" ${compiler_flag} "${${compiler_flag}}")
    
    # /Wn -> /W4 (Warning Level)
    string(REGEX REPLACE "/W[0-4]" "/W4" ${compiler_flag} "${${compiler_flag}}")
    
    # /GR- (Disable Run-Time Type Information)
    string(REGEX REPLACE "/GR-?" "/GR-" ${compiler_flag} "${${compiler_flag}}")

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(${compiler_flag} "${${compiler_flag}} -Wno-type-limits")

  endif()
endforeach()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

file(GLOB_RECURSE bksge_headers CONFIGURE_DEPENDS include/bksge/*)
target_sources(${TARGET_NAME} INTERFACE ${bksge_headers})

target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

if (MSVC)
  # /WX (Treat all warnings as errors)
  target_compile_options(${TARGET_NAME} INTERFACE /WX)

  # C4103: alignment changed after including header, may be due to missing #pragma pack(pop)
  target_compile_options(${TARGET_NAME} INTERFACE /wd4103)

  # C4384: #pragma '...' should only be used at global scope
  target_compile_options(${TARGET_NAME} INTERFACE /wd4384)

  # /guard:cf (Enable Control Flow Guard)
  target_compile_options(${TARGET_NAME} INTERFACE /guard:cf)

  # /permissive- (Standards conformance)
  target_compile_options(${TARGET_NAME} INTERFACE /permissive-)

  # /bigobj (Increase Number of Sections in .obj file)
  target_compile_options(${TARGET_NAME} INTERFACE /bigobj)

  # /MP (Build with Multiple Processes)
  if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TARGET_NAME} INTERFACE /MP)
  endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${TARGET_NAME} INTERFACE -Wall -Wextra -Werror -Wno-mismatched-tags)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${TARGET_NAME} INTERFACE -Wall -Wextra -Werror -Wno-missing-field-initializers)
endif()

add_subdirectory(test)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  if(BKSGE_BUILD_TESTING)
    enable_testing()
    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
	add_executable(unit_test)
	target_link_libraries(unit_test
	  PRIVATE
		Bksge::${TARGET_NAME_BASE}_test
		GTest::gtest
		GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_test)
  endif()
endif()
