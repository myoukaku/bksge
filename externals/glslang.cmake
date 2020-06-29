message("Configuring glslang")

option(SKIP_GLSLANG_INSTALL "Skip installation" On)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(externals/glslang)

add_library(glslang-default-resource-limits-lib STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/externals/glslang/StandAlone/ResourceLimits.cpp)
target_include_directories(glslang-default-resource-limits-lib
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/externals/glslang)

message("")
