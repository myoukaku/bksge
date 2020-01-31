/**
 *	@file	physical_device_inl.hpp
 *
 *	@brief	PhysicalDevice クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PHYSICAL_DEVICE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PHYSICAL_DEVICE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
PhysicalDevice::PhysicalDevice(::VkPhysicalDevice const& physical_device)
	: m_physical_device(physical_device)
{
	vk::GetPhysicalDeviceMemoryProperties(physical_device, &m_memory_properties);

	vk::GetPhysicalDeviceQueueFamilyProperties(physical_device, &m_queue_family_properties_count, nullptr);
	std::vector<VkQueueFamilyProperties> props(m_queue_family_properties_count);
	vk::GetPhysicalDeviceQueueFamilyProperties(physical_device, &m_queue_family_properties_count, props.data());

	for (std::uint32_t i = 0; i < m_queue_family_properties_count; ++i)
	{
		if (props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			m_graphics_queue_family_index = i;
			break;
		}
	}
}

BKSGE_INLINE
PhysicalDevice::~PhysicalDevice()
{
}

BKSGE_INLINE ::VkPhysicalDeviceMemoryProperties const&
PhysicalDevice::GetMemoryProperties(void) const
{
	return m_memory_properties;
}

BKSGE_INLINE std::uint32_t
PhysicalDevice::GetGraphicsQueueFamilyIndex(void) const
{
	return m_graphics_queue_family_index;
}

BKSGE_INLINE std::uint32_t
PhysicalDevice::GetPresentQueueFamilyIndex(::VkSurfaceKHR surface) const
{
	for (std::uint32_t i = 0; i < m_queue_family_properties_count; i++)
	{
		::VkBool32 supports_present;
		vk::GetPhysicalDeviceSurfaceSupportKHR(
			m_physical_device, i, surface, &supports_present);
		if (supports_present == VK_TRUE)
		{
			return i;
		}
	}

	return UINT32_MAX;
}

#if 0
BKSGE_INLINE std::vector<::VkQueueFamilyProperties>
PhysicalDevice::GetQueueFamilyProperties()
{
	std::uint32_t queue_family_count = 0;
	vk::GetPhysicalDeviceQueueFamilyProperties(
		m_physical_device,
		&queue_family_count,
		nullptr);

	std::vector<::VkQueueFamilyProperties> queue_family_properties;
	queue_family_properties.resize(queue_family_count);
	vk::GetPhysicalDeviceQueueFamilyProperties(
		m_physical_device,
		&queue_family_count,
		queue_family_properties.data());

	return queue_family_properties;
}

BKSGE_INLINE std::vector<::VkSurfaceFormatKHR>
PhysicalDevice::GetSurfaceFormats(::VkSurfaceKHR surface)
{
	std::uint32_t count;
	vk::GetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, nullptr);

	std::vector<::VkSurfaceFormatKHR> formats;
	formats.resize(count);
	vk::GetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, formats.data());

	return formats;
}
#endif

BKSGE_INLINE ::VkPhysicalDeviceFeatures
PhysicalDevice::GetFeatures(void) const
{
	::VkPhysicalDeviceFeatures feature;
	vk::GetPhysicalDeviceFeatures(m_physical_device, &feature);
	return feature;
}

BKSGE_INLINE
PhysicalDevice::operator ::VkPhysicalDevice() const
{
	return m_physical_device;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PHYSICAL_DEVICE_INL_HPP
