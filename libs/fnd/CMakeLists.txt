cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME "bksge_fnd")

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(Bksge::fnd ALIAS ${TARGET_NAME})

set(SUBDIRECTORIES
	algorithm
	any
	array
	bigint
	bit
	cmath
	compare
	complex
	concepts
	config
	cstddef
	cstring
	debug
	deque
#	detail
	forward_list
	functional
	hash_functions
	ios
	iterator
	list
	map
	memory
	numbers
	numeric
	optional
	pair
	preprocessor
	random
	ranges
	ratio
	serialization
	set
	span
	static_string
	static_vector
	stdexcept
	string
	string_view
	tmp
	tpp
	tuple
	type_traits
	units
	unordered_map
	unordered_set
	utility
	variant
	vector)

foreach(SUBDIRECTORY ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIRECTORY})
	target_link_libraries(${TARGET_NAME} INTERFACE Bksge::${SUBDIRECTORY})
endforeach()

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
    
  endif()
endforeach()

add_library(bksge_fnd_test INTERFACE)
add_library(Bksge::fnd_test ALIAS bksge_fnd_test)
foreach(SUBDIRECTORY ${SUBDIRECTORIES})
	target_link_libraries(bksge_fnd_test INTERFACE Bksge::${SUBDIRECTORY}_test)
endforeach()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  if(BKSGE_BUILD_TESTING)
    enable_testing()
    option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../externals/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
	add_executable(unit_test)
	target_link_libraries(unit_test
	  PRIVATE
		Bksge::fnd_test
		GTest::gtest
		GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_test)
  endif()
endif()
