/**
 *	@file	instance.hpp
 *
 *	@brief	Instance クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INSTANCE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INSTANCE_HPP

#include <bksge/render/vulkan/detail/fwd/instance_fwd.hpp>
#include <bksge/render/vulkan/detail/physical_device.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <cstddef>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

struct ApplicationInfo : public ::VkApplicationInfo
{
	ApplicationInfo(void);
};

struct InstanceCreateInfo : public ::VkInstanceCreateInfo
{
	InstanceCreateInfo(void);

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
	explicit Instance(vk::InstanceCreateInfo const& info);

	~Instance();

	std::vector<vk::PhysicalDevice> EnumeratePhysicalDevices(void) const;

	operator ::VkInstance() const;

private:
	::VkInstance m_instance;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/instance_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_INSTANCE_HPP
