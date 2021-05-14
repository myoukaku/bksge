cmake_minimum_required(VERSION 3.12)

project(bksge LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#include(Dart)

option(BKSGE_UNITY_BUILD "Use Unity Builds" OFF)
option(BKSGE_BUILD_TESTING "" ON)

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
    # /Wn -> /W0 (Warning Level)
    if(${compiler_flag} MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W0" ${compiler_flag} "${${compiler_flag}}")
    else()
      set(${compiler_flag} "${${compiler_flag}} /W0")
    endif()

    # /MD[d] -> /MT[d] (Run-Time Library)
    if(${compiler_flag} MATCHES "/MD")
	  if(CMAKE_BUILD_TYPE MATCHES "Debug")
	    string(REGEX REPLACE "/MDd?" "/MTd" ${compiler_flag} "${${compiler_flag}}")
      else()
	    string(REGEX REPLACE "/MDd?" "/MT" ${compiler_flag} "${${compiler_flag}}")
      endif()
    else()
	  if(CMAKE_BUILD_TYPE MATCHES "Debug")
	    set(${compiler_flag} "${${compiler_flag}} /MTd")
      else()
	    set(${compiler_flag} "${${compiler_flag}} /MT")
      endif()
    endif()

    # /ZI -> /Zi
    if(${compiler_flag} MATCHES "/ZI")
	  string(REGEX REPLACE "/ZI" "/Zi" ${compiler_flag} "${${compiler_flag}}")
    else()
	  set(${compiler_flag} "${${compiler_flag}} /Zi")
    endif()

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(${compiler_flag} "${${compiler_flag}} -Wno-type-limits")

  endif()
endforeach()

include(externals/glslang.cmake)
include(externals/spirv-cross.cmake)
include(externals/vulkan-loader.cmake)
include(externals/vulkan-headers.cmake)

foreach(compiler_flag ${compiler_flags})
  if (MSVC)
    # /Wn -> /W4 (Warning Level)
    if(${compiler_flag} MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W4" ${compiler_flag} "${${compiler_flag}}")
    else()
      set(${compiler_flag} "${${compiler_flag}} /W4")
    endif()

	# /WX (Treat all warnings as errors)
    set(${compiler_flag} "${${compiler_flag}} /WX")

	# Suppress compiler warnings

	# C4103: alignment changed after including header, may be due to missing #pragma pack(pop)
    set(${compiler_flag} "${${compiler_flag}} /wd4103")

	# C4384: #pragma '...' should only be used at global scope
    set(${compiler_flag} "${${compiler_flag}} /wd4384")

	# /guard:cf (Enable Control Flow Guard)
    set(${compiler_flag} "${${compiler_flag}} /guard:cf")

	# /MP (Build with Multiple Processes)
	if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      set(${compiler_flag} "${${compiler_flag}} /MP")
	endif()

	# /GR- (Disable Run-Time Type Information)
    string(REGEX REPLACE "/GR-?" "/GR-" ${compiler_flag} "${${compiler_flag}}")

	# /permissive- (Standards conformance)
    set(${compiler_flag} "${${compiler_flag}} /permissive-")

	# /bigobj (Increase Number of Sections in .obj file)
    set(${compiler_flag} "${${compiler_flag}} /bigobj")

	# /Bt
    #set(${compiler_flag} "${${compiler_flag}} /Bt")

	# /d2cgsummary
    #set(${compiler_flag} "${${compiler_flag}} /d2cgsummary")

	# /d1reportTime (compiler frontend spends time)
    #set(${compiler_flag} "${${compiler_flag}} /d1reportTime")

	# /Zc:preprocessor
    #set(${compiler_flag} "${${compiler_flag}} /Zc:preprocessor /Wv:18")

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(${compiler_flag} "${${compiler_flag}} -Wall -Wextra -Werror -Wno-mismatched-tags")

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(${compiler_flag} "${${compiler_flag}} -Wall -Wextra -Werror -Wno-missing-field-initializers")

  endif()
endforeach()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

SET(COVERAGE OFF CACHE BOOL "Coverage")
if (COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
#message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
#message(STATUS "CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
#message(STATUS "CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
#message(STATUS "CMAKE_C_FLAGS_MINSIZEREL: ${CMAKE_C_FLAGS_MINSIZEREL}")
#message(STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")

file(GLOB_RECURSE bksge_sources CONFIGURE_DEPENDS src/bksge/*)
add_library(bksge STATIC ${bksge_sources})
if(BKSGE_UNITY_BUILD)
  set_target_properties(bksge PROPERTIES UNITY_BUILD ON)
endif()
target_include_directories(bksge PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
target_link_libraries(bksge PRIVATE OpenGL::GL)

find_package(Vulkan REQUIRED)
target_link_libraries(bksge PUBLIC Vulkan::Vulkan)

target_link_libraries(bksge PRIVATE glslang SPIRV)
target_link_libraries(bksge PRIVATE spirv-cross-glsl)

if(MINGW)
  target_link_libraries(bksge -ld3d11 -ld3dcompiler -ldinput8 -ldxguid)
endif()

if(BKSGE_BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
add_subdirectory(samples)
