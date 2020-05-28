message("Configuring Vulkan-Headers")

#add_library(vulkan-headers INTERFACE)
target_include_directories(vulkan-headers
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/externals/Vulkan-Headers/include
)

message("")
