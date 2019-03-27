cmake_minimum_required(VERSION 3.12)
project(bksge CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(Dart)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(compiler_flags
  CMAKE_CXX_FLAGS
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_MINSIZEREL
  CMAKE_CXX_FLAGS_RELWITHDEBINFO
  CMAKE_C_FLAGS
  CMAKE_C_FLAGS_DEBUG
  CMAKE_C_FLAGS_RELEASE
  CMAKE_C_FLAGS_MINSIZEREL
  CMAKE_C_FLAGS_RELWITHDEBINFO)

foreach(compiler_flag ${compiler_flags})
  if (MSVC)
    # /Wn -> /W4 (Warning Level)
    if(${compiler_flag} MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W4" ${compiler_flag} "${${compiler_flag}}")
    else()
      set(${compiler_flag} "${${compiler_flag}} /W4")
    endif()

    # /MD[d] -> /MT[d] (Run-Time Library)
	string(REPLACE "/MD" "/MT" ${compiler_flag} "${${compiler_flag}}")

	# /WX (Treat all warnings as errors)
    set(${compiler_flag} "${${compiler_flag}} /WX")

	# /MP (Build with Multiple Processes)
    set(${compiler_flag} "${${compiler_flag}} /MP")

	# /bigobj (Increase Number of Sections in .obj file)
    set(${compiler_flag} "${${compiler_flag}} /bigobj")

	# /Bt
    #set(${compiler_flag} "${${compiler_flag}} /Bt")

	# /d2cgsummary
    #set(${compiler_flag} "${${compiler_flag}} /d2cgsummary")

	# /d1reportTime (compiler frontend spends time)
    #set(${compiler_flag} "${${compiler_flag}} /d1reportTime")

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(${compiler_flag} "${${compiler_flag}} -Wall -Wextra -Werror -Wno-mismatched-tags")

  elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(${compiler_flag} "${${compiler_flag}} -Wall -Wextra -Werror")

  endif()
endforeach()

SET(COVERAGE OFF CACHE BOOL "Coverage")
if (COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

enable_testing()

find_package(OpenGL REQUIRED)
message(STATUS ${OPENGL_LIBRARIES})
message(STATUS ${OPENGL_INCLUDE_DIR})

file(GLOB_RECURSE bksge_sources src/bksge/*)
add_library(bksge STATIC ${bksge_sources})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(bksge ${OPENGL_LIBRARIES})

include(${PROJECT_SOURCE_DIR}/cmake/assign_source_group.cmake)
assign_source_group(${bksge_sources})

if(WIN32)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_link_libraries(bksge -lopengl32 -ldinput8 -ldxguid)
  endif()
endif()

add_subdirectory(test)
add_subdirectory(samples)
