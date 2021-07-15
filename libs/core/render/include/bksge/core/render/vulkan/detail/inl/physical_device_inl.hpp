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
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
PhysicalDevice::PhysicalDevice(::VkPhysicalDevice const& physical_device)
	: m_physical_device(physical_device)
{}

BKSGE_INLINE
PhysicalDevice::~PhysicalDevice()
{}

BKSGE_INLINE ::VkDevice
PhysicalDevice::CreateDevice(vk::DeviceCreateInfo const& create_info)
{
	::VkDevice device;
	vk::CreateDevice(m_physical_device, &create_info, nullptr, &device);
	return device;
}

BKSGE_INLINE bksge::vector<::VkLayerProperties>
PhysicalDevice::EnumerateDeviceLayerProperties(void) const
{
	for (;;)
	{
		std::uint32_t count;
		vk::EnumerateDeviceLayerProperties(
			m_physical_device, &count, nullptr);

		if (count == 0)
		{
			return {};
		}

		bksge::vector<::VkLayerProperties> layer_properties(count);
		auto res = vk::EnumerateDeviceLayerProperties(
			m_physical_device, &count, layer_properties.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}

		return layer_properties;
	}
}

BKSGE_INLINE bksge::vector<::VkExtensionProperties>
PhysicalDevice::EnumerateDeviceExtensionProperties(char const* layer_name) const
{
	for (;;)
	{
		std::uint32_t count;
		vk::EnumerateDeviceExtensionProperties(
			m_physical_device, layer_name, &count, nullptr);

		if (count == 0)
		{
			return {};
		}

		bksge::vector<::VkExtensionProperties> extension_properties(count);
		auto res = vk::EnumerateDeviceExtensionProperties(
			m_physical_device, layer_name, &count, extension_properties.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}

		return extension_properties;
	}
}

BKSGE_INLINE bksge::vector<::VkQueueFamilyProperties>
PhysicalDevice::GetQueueFamilyProperties(void) const
{
	std::uint32_t count = 0;
	vk::GetPhysicalDeviceQueueFamilyProperties(
		m_physical_device, &count, nullptr);

	if (count == 0)
	{
		return {};
	}

	bksge::vector<::VkQueueFamilyProperties> props(count);
	vk::GetPhysicalDeviceQueueFamilyProperties(
		m_physical_device, &count, props.data());
	return props;
}

BKSGE_INLINE std::uint32_t
PhysicalDevice::GetGraphicsQueueFamilyIndex(void) const
{
	auto const queue_family_properties = GetQueueFamilyProperties();

	for (std::uint32_t i = 0; i < queue_family_properties.size(); ++i)
	{
		if (queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			return i;
		}
	}

	return UINT32_MAX;
}

BKSGE_INLINE std::uint32_t
PhysicalDevice::GetPresentQueueFamilyIndex(::VkSurfaceKHR surface) const
{
	auto const queue_family_properties = GetQueueFamilyProperties();

	for (std::uint32_t i = 0; i < queue_family_properties.size(); i++)
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

BKSGE_INLINE bksge::vector<::VkSurfaceFormatKHR>
PhysicalDevice::GetSurfaceFormats(::VkSurfaceKHR surface) const
{
	for (;;)
	{
		std::uint32_t count;
		vk::GetPhysicalDeviceSurfaceFormatsKHR(
			m_physical_device, surface, &count, nullptr);

		if (count == 0)
		{
			return {};
		}

		bksge::vector<::VkSurfaceFormatKHR> formats(count);
		auto res = vk::GetPhysicalDeviceSurfaceFormatsKHR(
			m_physical_device, surface, &count, formats.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}

		return formats;
	}
}

BKSGE_INLINE ::VkSurfaceCapabilitiesKHR
PhysicalDevice::GetSurfaceCapabilities(::VkSurfaceKHR surface) const
{
	::VkSurfaceCapabilitiesKHR surface_capabilities;
	vk::GetPhysicalDeviceSurfaceCapabilitiesKHR(
		m_physical_device, surface, &surface_capabilities);
	return surface_capabilities;
}

BKSGE_INLINE ::VkPhysicalDeviceMemoryProperties
PhysicalDevice::GetMemoryProperties(void) const
{
	::VkPhysicalDeviceMemoryProperties memory_properties;
	vk::GetPhysicalDeviceMemoryProperties(m_physical_device, &memory_properties);
	return memory_properties;
}

BKSGE_INLINE ::VkPhysicalDeviceProperties
PhysicalDevice::GetProperties(void) const
{
	::VkPhysicalDeviceProperties properties;
	vk::GetPhysicalDeviceProperties(m_physical_device, &properties);
	return properties;
}

BKSGE_INLINE ::VkPhysicalDeviceFeatures
PhysicalDevice::GetFeatures(void) const
{
	::VkPhysicalDeviceFeatures features;
	vk::GetPhysicalDeviceFeatures(m_physical_device, &features);
	return features;
}

BKSGE_INLINE ::VkFormatProperties
PhysicalDevice::GetFormatProperties(::VkFormat format) const
{
	::VkFormatProperties props;
	vk::GetPhysicalDeviceFormatProperties(m_physical_device, format, &props);
	return props;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PHYSICAL_DEVICE_INL_HPP
