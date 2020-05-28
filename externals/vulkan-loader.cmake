message("Configuring Vulkan-Loader")

set(VulkanHeaders_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/Vulkan-Headers/include)
set(VulkanRegistry_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/Vulkan-Headers/registry)
option(BUILD_WSI_WAYLAND_SUPPORT "Build Wayland WSI support" OFF)
add_subdirectory(externals/Vulkan-Loader)

message("")
