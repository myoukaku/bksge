/**
 *	@file	device_inl.hpp
 *
 *	@brief	Device クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Device::Device(vulkan::PhysicalDeviceSharedPtr const& physical_device)
	: m_physical_device(physical_device)
	, m_device(VK_NULL_HANDLE)
{
	std::vector<char const*> layer_names;
	std::vector<char const*> extension_names;

#if 0	// 可能なレイヤーと拡張を全て追加

	// これらのインスタンスは vk::CreateDevice を呼び出すまで生きていなければいけない
	// (layer_names 等には char const* をコピーしているだけなので)
	auto extension_properties = vk::EnumerateDeviceExtensionProperties(*physical_device, nullptr);
	auto layer_properties     = vk::EnumerateDeviceLayerProperties(*physical_device);

	for (auto&& layer_property : layer_properties)
	{
		layer_names.push_back(layer_property.layerName);
		auto layer_extension_properties =
			vk::EnumerateDeviceExtensionProperties(
				*physical_device, layer_property.layerName);
		for (auto&& layer_extension_property : layer_extension_properties)
		{
			extension_properties.push_back(layer_extension_property);
		}
	}

	for (auto&& extension_property : extension_properties)
	{
		extension_names.push_back(extension_property.extensionName);
	}

#else	// 使うものだけを手動で追加

	extension_names.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	extension_names.push_back(VK_KHR_MAINTENANCE1_EXTENSION_NAME);

#endif

	float const queue_priorities = 0.0;

	vk::DeviceQueueCreateInfo queue_info;
	queue_info.flags            = 0;
	queue_info.queueFamilyIndex = physical_device->GetGraphicsQueueFamilyIndex();
	queue_info.queueCount       = 1;
	queue_info.pQueuePriorities = &queue_priorities;

	vk::DeviceCreateInfo info;
	info.SetQueueCreateInfos(&queue_info);
	info.SetEnabledLayerNames(layer_names);
	info.SetEnabledExtensionNames(extension_names);

	vk::CreateDevice(*physical_device, &info, nullptr, &m_device);
}

BKSGE_INLINE
Device::~Device()
{
	vk::DeviceWaitIdle(m_device);
	vk::DestroyDevice(m_device, nullptr);
}

BKSGE_INLINE
Device::operator ::VkDevice() const
{
	return m_device;
}

BKSGE_INLINE vulkan::PhysicalDeviceSharedPtr const&
Device::GetPhysicalDevice(void) const
{
	return m_physical_device;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
