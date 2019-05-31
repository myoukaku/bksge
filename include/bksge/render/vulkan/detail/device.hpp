/**
 *	@file	device.hpp
 *
 *	@brief	Device クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_DEVICE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_DEVICE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/physical_device.hpp>

namespace bksge
{

namespace render
{

namespace vk
{

struct DeviceQueueCreateInfo : public ::VkDeviceQueueCreateInfo
{
	DeviceQueueCreateInfo(void)
	{
		sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		pNext            = nullptr;
		flags            = 0;
		queueFamilyIndex = 0;
		queueCount       = 0;
		pQueuePriorities = nullptr;
	}
};

struct DeviceCreateInfo : public ::VkDeviceCreateInfo
{
	DeviceCreateInfo(void)
	{
		sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		pNext                   = nullptr;
		queueCreateInfoCount    = 0;
		pQueueCreateInfos       = nullptr;
		enabledLayerCount       = 0;
		ppEnabledLayerNames     = nullptr;
		enabledExtensionCount   = 0;
		ppEnabledExtensionNames = nullptr;
		pEnabledFeatures        = nullptr;
	}

	template <std::size_t N>
	void SetEnabledLayers(char const* (&layers)[N])
	{
		enabledLayerCount       = N;
		ppEnabledLayerNames     = layers;
	}

	template <std::size_t N>
	void SetEnabledExtensions(char const* (&extensions)[N])
	{
		enabledExtensionCount   = N;
		ppEnabledExtensionNames = extensions;
	}
};

class Device
{
public:
	explicit Device(vk::PhysicalDevice const& gpu, vk::DeviceCreateInfo const& info)
		: m_device(VK_NULL_HANDLE)
	{
		vk::CreateDevice(gpu, &info, nullptr, &m_device);
	}

	~Device()
	{
		vk::DestroyDevice(m_device, nullptr);
	}

	operator ::VkDevice() const
	{
		return m_device;
	}

private:
	::VkDevice m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_DEVICE_HPP
