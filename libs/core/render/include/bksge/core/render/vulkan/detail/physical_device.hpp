/**
 *	@file	physical_device.hpp
 *
 *	@brief	PhysicalDevice クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP

#include <bksge/core/render/vulkan/detail/fwd/physical_device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class PhysicalDevice
{
public:
	explicit PhysicalDevice(::VkPhysicalDevice const& physical_device);

	~PhysicalDevice();

	::VkDevice CreateDevice(vk::DeviceCreateInfo const& create_info);

	bksge::vector<::VkLayerProperties>	EnumerateDeviceLayerProperties(void) const;

	bksge::vector<::VkExtensionProperties> EnumerateDeviceExtensionProperties(char const* layer_name) const;

	bksge::vector<::VkQueueFamilyProperties> GetQueueFamilyProperties(void) const;

	bksge::uint32_t GetGraphicsQueueFamilyIndex(void) const;

	bksge::uint32_t GetPresentQueueFamilyIndex(::VkSurfaceKHR surface) const;

	bksge::vector<::VkSurfaceFormatKHR> GetSurfaceFormats(::VkSurfaceKHR surface) const;

	::VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(::VkSurfaceKHR surface) const;

	::VkPhysicalDeviceMemoryProperties GetMemoryProperties(void) const;

	::VkPhysicalDeviceProperties GetProperties(void) const;

	::VkPhysicalDeviceFeatures GetFeatures(void) const;

	::VkFormatProperties GetFormatProperties(::VkFormat format) const;

private:
	// noncopyable
	PhysicalDevice(PhysicalDevice const&) = delete;
	PhysicalDevice& operator=(PhysicalDevice const&) = delete;

private:
	::VkPhysicalDevice	m_physical_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/physical_device_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
