
message("Configuring glslang")
option(SKIP_GLSLANG_INSTALL "Skip installation" On)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(LLVM_USE_CRT_DEBUG   "MTd" CACHE STRING "" FORCE)
set(LLVM_USE_CRT_RELEASE "MT"  CACHE STRING "" FORCE)
add_subdirectory(glslang)

message("Configuring SPIRV-Cross")
add_subdirectory(SPIRV-Cross)
