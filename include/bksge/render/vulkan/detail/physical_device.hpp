/**
 *	@file	physical_device.hpp
 *
 *	@brief	PhysicalDevice クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vk
{

class PhysicalDevice
{
public:
	explicit PhysicalDevice(::VkPhysicalDevice const& physical_device)
		: m_physical_device(physical_device)
	{
	}

	~PhysicalDevice()
	{
	}

	std::vector<::VkQueueFamilyProperties> GetQueueFamilyProperties()
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

	std::vector<::VkSurfaceFormatKHR> GetSurfaceFormats(::VkSurfaceKHR surface)
	{
		std::uint32_t count;
		vk::GetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, nullptr);

		std::vector<::VkSurfaceFormatKHR> formats;
		formats.resize(count);
		vk::GetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, surface, &count, formats.data());

		return formats;
	}

	operator ::VkPhysicalDevice() const
	{
		return m_physical_device;
	}

private:
	::VkPhysicalDevice m_physical_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
