/**
 *	@file	device.hpp
 *
 *	@brief	Device クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP

#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/physical_device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace vk
{

struct DeviceQueueCreateInfo : public ::VkDeviceQueueCreateInfo
{
	DeviceQueueCreateInfo(void);
};

struct DeviceCreateInfo : public ::VkDeviceCreateInfo
{
	DeviceCreateInfo(void);

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
	explicit Device(
		vk::PhysicalDevice const& gpu,
		vk::DeviceCreateInfo const& info);

	~Device();

	operator ::VkDevice() const;

private:
	::VkDevice m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/device_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP
