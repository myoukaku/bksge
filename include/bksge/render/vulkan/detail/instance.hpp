/**
 *	@file	instance.hpp
 *
 *	@brief	Instance クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INSTANCE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INSTANCE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/physical_device.hpp>

namespace bksge
{

namespace render
{

namespace vk
{

struct ApplicationInfo : public ::VkApplicationInfo
{
	ApplicationInfo(void)
	{
		sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		pNext              = nullptr;
		pApplicationName   = nullptr;
		applicationVersion = 0;
		pEngineName        = nullptr;
		engineVersion      = 0;
		apiVersion         = 0;
	}
};

struct InstanceCreateInfo : public ::VkInstanceCreateInfo
{
	InstanceCreateInfo(void)
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

class Instance
{
public:
	explicit Instance(vk::InstanceCreateInfo const& info)
		: m_instance(VK_NULL_HANDLE)
	{
		vk::CreateInstance(&info, nullptr, &m_instance);
	}

	~Instance()
	{
		vk::DestroyInstance(m_instance, nullptr);
	}

	std::vector<vk::PhysicalDevice> EnumeratePhysicalDevices(void) const
	{
		std::uint32_t gpu_count = 0;
		vk::EnumeratePhysicalDevices(m_instance, &gpu_count, nullptr);
		std::vector<::VkPhysicalDevice> gpus;
		gpus.resize(gpu_count);
		vk::EnumeratePhysicalDevices(m_instance, &gpu_count, gpus.data());

		std::vector<vk::PhysicalDevice> result(gpus.begin(), gpus.end());
		return result;
	}

	operator ::VkInstance() const
	{
		return m_instance;
	}

private:
	::VkInstance m_instance;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_INSTANCE_HPP
