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
//#include <bksge/fnd/vector.hpp>

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

	::VkPhysicalDeviceMemoryProperties const& memory_properties(void) const;

	bksge::uint32_t graphics_queue_family_index(void) const;

	bksge::uint32_t GetPresentQueueFamilyIndex(::VkSurfaceKHR surface) const;

	//bksge::vector<::VkQueueFamilyProperties> GetQueueFamilyProperties();

	//bksge::vector<::VkSurfaceFormatKHR> GetSurfaceFormats(::VkSurfaceKHR surface);

	::VkPhysicalDeviceFeatures const& features(void) const;

	::VkFormatProperties GetFormatProperties(::VkFormat format) const;

	operator ::VkPhysicalDevice() const;

private:
	// noncopyable
	PhysicalDevice(PhysicalDevice const&) = delete;
	PhysicalDevice& operator=(PhysicalDevice const&) = delete;

private:
	::VkPhysicalDevice					m_physical_device;
	::VkPhysicalDeviceMemoryProperties	m_memory_properties;
	::VkPhysicalDeviceFeatures			m_features;
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
