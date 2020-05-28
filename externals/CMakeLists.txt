cmake_minimum_required(VERSION 3.12)


set(ENABLE_STATIC_LOADER ON CACHE BOOL "")
add_subdirectory(Vulkan-Headers)
if (DEFINED Vulkan-Headers_SOURCE_DIR)
	message(STATUS "Using Vulkan headers from ${Vulkan-Headers_SOURCE_DIR}")
	set(VulkanHeaders_INCLUDE_DIR "${Vulkan-Headers_SOURCE_DIR}/include" PARENT_SCOPE)
	set(VulkanHeaders_INCLUDE_DIRS "${VulkanHeaders_INCLUDE_DIR}" PARENT_SCOPE)
	set(VulkanRegistry_DIR "${Vulkan-Headers_SOURCE_DIR}/registry")
	set(VulkanRegistry_DIRS "${VulkanRegistry_DIR}")
else()
	find_package(VulkanHeaders)
endif()

add_subdirectory(Vulkan-Loader)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(glslang)

add_subdirectory(SPIRV-Cross)
