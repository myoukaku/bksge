/**
 *	@file	physical_device.hpp
 *
 *	@brief	PhysicalDevice クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP

#include <bksge/render/vulkan/detail/fwd/physical_device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

class PhysicalDevice
{
public:
	explicit PhysicalDevice(::VkPhysicalDevice const& physical_device);

	~PhysicalDevice();

	std::vector<::VkQueueFamilyProperties> GetQueueFamilyProperties();

	std::vector<::VkSurfaceFormatKHR> GetSurfaceFormats(::VkSurfaceKHR surface);

	operator ::VkPhysicalDevice() const;

private:
	::VkPhysicalDevice m_physical_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/physical_device_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_PHYSICAL_DEVICE_HPP
