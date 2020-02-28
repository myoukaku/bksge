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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Device
{
public:
	explicit Device(
		vulkan::PhysicalDeviceSharedPtr const& physical_device);

	~Device();

	vulkan::PhysicalDeviceSharedPtr const& GetPhysicalDevice(void) const;

	::VkCommandPool	CreateCommandPool(
		::VkCommandPoolCreateFlags flags,
		std::uint32_t queue_family_index);

	void DestroyCommandPool(::VkCommandPool command_pool);

	operator ::VkDevice() const;

private:
	// noncopyable
	Device(Device const&) = delete;
	Device& operator=(Device const&) = delete;

private:
	vulkan::PhysicalDeviceSharedPtr	m_physical_device;
	::VkDevice						m_device;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/device_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_HPP
