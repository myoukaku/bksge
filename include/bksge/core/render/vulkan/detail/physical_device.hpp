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
#include <vector>

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

	::VkPhysicalDeviceMemoryProperties const& GetMemoryProperties(void) const;

	bksge::uint32_t GetGraphicsQueueFamilyIndex(void) const;

	bksge::uint32_t GetPresentQueueFamilyIndex(::VkSurfaceKHR surface) const;

	//std::vector<::VkQueueFamilyProperties> GetQueueFamilyProperties();

	//std::vector<::VkSurfaceFormatKHR> GetSurfaceFormats(::VkSurfaceKHR surface);

	::VkPhysicalDeviceFeatures GetFeatures(void) const;

	operator ::VkPhysicalDevice() const;

private:
	// noncopyable
	PhysicalDevice(PhysicalDevice const&) = delete;
	PhysicalDevice& operator=(PhysicalDevice const&) = delete;

private:
	::VkPhysicalDevice					m_physical_device;
	::VkPhysicalDeviceMemoryProperties	m_memory_properties;
	bksge::uint32_t						m_queue_family_properties_count = 0;
	bksge::uint32_t						m_graphics_queue_family_index = UINT32_MAX;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/physical_device_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
