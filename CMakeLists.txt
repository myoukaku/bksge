cmake_minimum_required(VERSION 3.12)

project(bksge LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BKSGE_UNITY_BUILD "Use Unity Builds" OFF)
option(BKSGE_BUILD_TESTING "Build tests" ON)
option(BKSGE_BUILD_SAMPLES "Build samples" ON)
option(BKSGE_COVERAGE "Coverage" OFF)

# CMAKE_CXX_FLAGS_* を変更する前にexternalsを追加する
add_subdirectory(externals)

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

    # /Wn -> /W4 (Warning Level)
    if(${compiler_flag} MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W4" ${compiler_flag} "${${compiler_flag}}")
    else()
      set(${compiler_flag} "${${compiler_flag}} /W4")
    endif()

	# /GR- (Disable Run-Time Type Information)
    string(REGEX REPLACE "/GR-?" "/GR-" ${compiler_flag} "${${compiler_flag}}")

  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(${compiler_flag} "${${compiler_flag}} -Wno-type-limits")

  endif()
endforeach()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

add_library(bksge STATIC)

file(GLOB_RECURSE bksge_sources CONFIGURE_DEPENDS src/bksge/*)
file(GLOB_RECURSE bksge_headers CONFIGURE_DEPENDS include/bksge/*)
target_sources(bksge PRIVATE ${bksge_sources} ${bksge_headers})

target_include_directories(bksge PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (MSVC)
  # /WX (Treat all warnings as errors)
  target_compile_options(bksge PRIVATE /WX)

  # C4103: alignment changed after including header, may be due to missing #pragma pack(pop)
  target_compile_options(bksge PUBLIC /wd4103)

  # C4384: #pragma '...' should only be used at global scope
  target_compile_options(bksge PUBLIC /wd4384)

  # /guard:cf (Enable Control Flow Guard)
  target_compile_options(bksge PUBLIC /guard:cf)

  # /permissive- (Standards conformance)
  target_compile_options(bksge PUBLIC /permissive-)

  # /bigobj (Increase Number of Sections in .obj file)
  target_compile_options(bksge PUBLIC /bigobj)

  # /MP (Build with Multiple Processes)
  if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(bksge PUBLIC /MP)
  endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(bksge PRIVATE -Wall -Wextra -Werror -Wno-mismatched-tags)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(bksge PRIVATE -Wall -Wextra -Werror -Wno-missing-field-initializers)
endif()

if (BKSGE_COVERAGE)
  target_compile_options(bksge PRIVATE --coverage)
endif()

if(BKSGE_UNITY_BUILD)
  set_target_properties(bksge PROPERTIES UNITY_BUILD ON)
endif()

find_package(OpenGL REQUIRED)
target_link_libraries(bksge PRIVATE OpenGL::GL)

find_package(Vulkan REQUIRED)
target_link_libraries(bksge PRIVATE Vulkan::Vulkan)

target_link_libraries(bksge PRIVATE glslang SPIRV)
target_link_libraries(bksge PRIVATE spirv-cross-glsl)

if(MINGW)
  target_link_libraries(bksge -ld3d11 -ld3dcompiler -ldinput8 -ldxguid)
endif()

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

if(BKSGE_BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

if(BKSGE_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()
