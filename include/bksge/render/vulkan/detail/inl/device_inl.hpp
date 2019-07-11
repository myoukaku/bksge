/**
 *	@file	device_inl.hpp
 *
 *	@brief	Device クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/vulkan/detail/physical_device.hpp>
#include <bksge/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
DeviceQueueCreateInfo::DeviceQueueCreateInfo(void)
{
	sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	pNext            = nullptr;
	flags            = 0;
	queueFamilyIndex = 0;
	queueCount       = 0;
	pQueuePriorities = nullptr;
}

BKSGE_INLINE
DeviceCreateInfo::DeviceCreateInfo(void)
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

BKSGE_INLINE
Device::Device(vk::PhysicalDevice const& gpu, vk::DeviceCreateInfo const& info)
	: m_device(VK_NULL_HANDLE)
{
	vk::CreateDevice(gpu, &info, nullptr, &m_device);
}

BKSGE_INLINE
Device::~Device()
{
	vk::DestroyDevice(m_device, nullptr);
}

BKSGE_INLINE
Device::operator ::VkDevice() const
{
	return m_device;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
