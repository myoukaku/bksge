cmake_minimum_required(VERSION 3.12)
project(bksge CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(Dart)

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

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

foreach(compiler_flag ${compiler_flags})
  if (MSVC)
    # /ZI -> /Zi
    if(${compiler_flag} MATCHES "/ZI")
	  string(REGEX REPLACE "/ZI" "/Zi" ${compiler_flag} "${${compiler_flag}}")
    else()
	  set(${compiler_flag} "${${compiler_flag}} /Zi")
    endif()
  endif()
endforeach()

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)

download_project(
  PROJ Vulkan-Headers
  GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  QUIET)
message(STATUS ${Vulkan-Headers_SOURCE_DIR})
message(STATUS ${Vulkan-Headers_BINARY_DIR})
add_subdirectory(${Vulkan-Headers_SOURCE_DIR} ${Vulkan-Headers_BINARY_DIR})

if (DEFINED Vulkan-Headers_SOURCE_DIR)
    message(STATUS "Using Vulkan headers from ${Vulkan-Headers_SOURCE_DIR}")
    set(VulkanHeaders_INCLUDE_DIR "${Vulkan-Headers_SOURCE_DIR}/include")
    set(VulkanHeaders_INCLUDE_DIRS "${VulkanHeaders_INCLUDE_DIR}")
    set(VulkanRegistry_DIR "${Vulkan-Headers_SOURCE_DIR}/registry")
    set(VulkanRegistry_DIRS "${VulkanRegistry_DIR}")
else()
    find_package(VulkanHeaders)
endif()
message(STATUS ${VulkanHeaders_INCLUDE_DIR})
#message(STATUS ${VulkanHeaders_LIBRARIES})
message(STATUS ${VulkanRegistry_DIR})

download_project(
  PROJ Vulkan-Loader
  GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Loader.git
  GIT_TAG master
  UPDATE_DISCONNECTED 1
  QUIET)
message(STATUS ${Vulkan-Loader_SOURCE_DIR})
message(STATUS ${Vulkan-Loader_BINARY_DIR})
add_subdirectory(${Vulkan-Loader_SOURCE_DIR} ${Vulkan-Loader_BINARY_DIR})

foreach(compiler_flag ${compiler_flags})
  if (MSVC)
    # /Wn -> /W4 (Warning Level)
    if(${compiler_flag} MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W4" ${compiler_flag} "${${compiler_flag}}")
    else()
      set(${compiler_flag} "${${compiler_flag}} /W4")
    endif()

    # /MD[d] -> /MT[d] (Run-Time Library)
    if(${compiler_flag} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${compiler_flag} "${${compiler_flag}}")
    endif()

    # /ZI -> /Zi
    if(${compiler_flag} MATCHES "/ZI")
	  string(REGEX REPLACE "/ZI" "/Zi" ${compiler_flag} "${${compiler_flag}}")
    else()
	  set(${compiler_flag} "${${compiler_flag}} /Zi")
    endif()

	# /guard:cf (Enable Control Flow Guard)
    set(${compiler_flag} "${${compiler_flag}} /guard:cf")

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

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(${compiler_flag} "${${compiler_flag}} -Wall -Wextra -Werror")

  endif()
endforeach()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

SET(COVERAGE OFF CACHE BOOL "Coverage")
if (COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

enable_testing()

find_package(OpenGL REQUIRED)
message(STATUS ${OPENGL_LIBRARIES})
message(STATUS ${OPENGL_INCLUDE_DIR})

message(STATUS ${CMAKE_CXX_FLAGS})
message(STATUS ${CMAKE_CXX_FLAGS_DEBUG})
message(STATUS ${CMAKE_CXX_FLAGS_RELEASE})

file(GLOB_RECURSE bksge_sources src/bksge/*)
add_library(bksge STATIC ${bksge_sources})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${VulkanHeaders_INCLUDE_DIR})

target_link_libraries(bksge ${OPENGL_LIBRARIES})
link_directories("${Vulkan-Loader_BINARY_DIR}/loader")
target_link_libraries(bksge vulkan-1)

include(${PROJECT_SOURCE_DIR}/cmake/assign_source_group.cmake)
assign_source_group(${bksge_sources})

if(MINGW)
  target_link_libraries(bksge -lopengl32 -ld3d11 -ld3dcompiler -ldinput8 -ldxguid)
endif()

add_subdirectory(test)
add_subdirectory(samples)
