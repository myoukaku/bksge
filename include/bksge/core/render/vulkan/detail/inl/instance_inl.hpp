/**
 *	@file	instance_inl.hpp
 *
 *	@brief	Instance クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/instance.hpp>
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
ApplicationInfo::ApplicationInfo(void)
{
	sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	pNext              = nullptr;
	pApplicationName   = nullptr;
	applicationVersion = 0;
	pEngineName        = nullptr;
	engineVersion      = 0;
	apiVersion         = 0;
}

BKSGE_INLINE
InstanceCreateInfo::InstanceCreateInfo(void)
{
	sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	pNext                   = nullptr;
	flags                   = 0;
	pApplicationInfo        = nullptr;
	enabledLayerCount       = 0;
	ppEnabledLayerNames     = nullptr;
	enabledExtensionCount   = 0;
	ppEnabledExtensionNames = nullptr;
}

BKSGE_INLINE
Instance::Instance(vk::InstanceCreateInfo const& info)
	: m_instance(VK_NULL_HANDLE)
{
	vk::CreateInstance(&info, nullptr, &m_instance);
}

BKSGE_INLINE
Instance::~Instance()
{
	vk::DestroyInstance(m_instance, nullptr);
}

BKSGE_INLINE std::vector<vk::PhysicalDevice>
Instance::EnumeratePhysicalDevices(void) const
{
	std::uint32_t gpu_count = 0;
	vk::EnumeratePhysicalDevices(m_instance, &gpu_count, nullptr);
	std::vector<::VkPhysicalDevice> gpus;
	gpus.resize(gpu_count);
	vk::EnumeratePhysicalDevices(m_instance, &gpu_count, gpus.data());

	std::vector<vk::PhysicalDevice> result(gpus.begin(), gpus.end());
	return result;
}

BKSGE_INLINE
Instance::operator ::VkInstance() const
{
	return m_instance;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INSTANCE_INL_HPP
