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

namespace vk
{

BKSGE_INLINE
PhysicalDevice::PhysicalDevice(::VkPhysicalDevice const& physical_device)
	: m_physical_device(physical_device)
{
}

BKSGE_INLINE
PhysicalDevice::~PhysicalDevice()
{
}

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

BKSGE_INLINE
PhysicalDevice::operator ::VkPhysicalDevice() const
{
	return m_physical_device;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PHYSICAL_DEVICE_INL_HPP
