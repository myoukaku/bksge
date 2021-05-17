message("Configuring glslang")

option(SKIP_GLSLANG_INSTALL "Skip installation" On)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(externals/glslang)
