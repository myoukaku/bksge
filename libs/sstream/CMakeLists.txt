cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME "bksge_sstream")

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(Bksge::sstream ALIAS ${TARGET_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BKSGE_UNITY_BUILD "Use Unity Builds" OFF)
option(BKSGE_BUILD_TESTING "Build tests" ON)
option(BKSGE_BUILD_SAMPLES "Build samples" ON)
option(BKSGE_COVERAGE "Coverage" OFF)

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
target_sources(${TARGET_NAME} PRIVATE ${bksge_headers})

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
