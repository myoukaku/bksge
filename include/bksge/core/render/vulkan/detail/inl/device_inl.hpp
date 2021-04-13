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
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/algorithm/ranges/find.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline bksge::vector<bksge::string>
EnumerateDeviceLayerNames(::VkPhysicalDevice physical_device)
{
	bksge::vector<bksge::string> result;

	auto layer_properties = vk::EnumerateDeviceLayerProperties(physical_device);
	for (auto&& layer_property : layer_properties)
	{
		result.push_back(layer_property.layerName);
	}

	return result;
}

inline bksge::vector<bksge::string>
EnumerateDeviceExtensionNames(::VkPhysicalDevice physical_device)
{
	bksge::vector<bksge::string> result;

	auto extension_properties =
		vk::EnumerateDeviceExtensionProperties(physical_device, nullptr);
	for (auto&& extension_property : extension_properties)
	{
		result.push_back(extension_property.extensionName);
	}

	auto layer_properties = vk::EnumerateDeviceLayerProperties(physical_device);
	for (auto&& layer_property : layer_properties)
	{
		auto layer_extension_properties =
			vk::EnumerateDeviceExtensionProperties(physical_device, layer_property.layerName);
		for (auto&& layer_extension_property : layer_extension_properties)
		{
			result.push_back(layer_extension_property.extensionName);
		}
	}

	return result;
}

}	// namespace detail

BKSGE_INLINE
Device::Device(vulkan::PhysicalDeviceSharedPtr const& physical_device)
	: m_physical_device(physical_device)
	, m_device(VK_NULL_HANDLE)
{
	bksge::vector<char const*> layer_names;
	{
		// 追加可能なレイヤーを全てリストアップ
		auto const available_layer_names =
			detail::EnumerateDeviceLayerNames(*physical_device);

		// 追加したいレイヤー
		bksge::vector<char const*> desired_layer_names =
		{
#if defined(_DEBUG)
			"VK_LAYER_KHRONOS_validation",
			"VK_LAYER_LUNARG_standard_validation",
#endif
		};

		// 可能であればレイヤーを追加
		for (auto desired_layer_name: desired_layer_names)
		{
			if (bksge::ranges::find(available_layer_names, desired_layer_name) != available_layer_names.end())
			{
				layer_names.push_back(desired_layer_name);
			}
		}
	}

	bksge::vector<char const*> extension_names;
	{
		// 追加可能な拡張を全てリストアップ
		auto const available_extension_names =
			detail::EnumerateDeviceExtensionNames(*physical_device);

		// 追加したい拡張
		bksge::vector<char const*> desired_extension_names =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
			VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME,
			VK_KHR_MAINTENANCE1_EXTENSION_NAME,
		};

		// 可能であれば拡張を追加
		for (auto desired_extension_name: desired_extension_names)
		{
			if (bksge::ranges::find(available_extension_names, desired_extension_name) != available_extension_names.end())
			{
				extension_names.push_back(desired_extension_name);
			}
		}
	}

	float const queue_priorities = 0.0;

	vk::DeviceQueueCreateInfo queue_info;
	queue_info.flags            = 0;
	queue_info.queueFamilyIndex = physical_device->GetGraphicsQueueFamilyIndex();
	queue_info.queueCount       = 1;
	queue_info.pQueuePriorities = &queue_priorities;

	auto const enabled_features = physical_device->GetFeatures();

	vk::DeviceCreateInfo info;
	info.SetQueueCreateInfos(&queue_info);
	info.SetEnabledLayerNames(layer_names);
	info.SetEnabledExtensionNames(extension_names);
	info.pEnabledFeatures = &enabled_features;

	vk::CreateDevice(*physical_device, &info, nullptr, &m_device);
}

BKSGE_INLINE
Device::~Device()
{
	this->WaitIdle();
	vk::DestroyDevice(m_device, nullptr);
}

BKSGE_INLINE void
Device::WaitIdle(void)
{
	vk::DeviceWaitIdle(m_device);
}

BKSGE_INLINE vulkan::PhysicalDeviceSharedPtr const&
Device::physical_device(void) const
{
	return m_physical_device;
}

BKSGE_INLINE ::VkCommandPool
Device::CreateCommandPool(
	::VkCommandPoolCreateFlags flags,
	bksge::uint32_t queue_family_index)
{
	vk::CommandPoolCreateInfo info;
	info.flags            = flags;
	info.queueFamilyIndex = queue_family_index;

	::VkCommandPool command_pool;
	vk::CreateCommandPool(m_device, &info, nullptr, &command_pool);
	return command_pool;
}

BKSGE_INLINE void
Device::DestroyCommandPool(::VkCommandPool command_pool)
{
	vk::DestroyCommandPool(m_device, command_pool, nullptr);
}

BKSGE_INLINE
Device::operator ::VkDevice() const
{
	return m_device;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEVICE_INL_HPP
