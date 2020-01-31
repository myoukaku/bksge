/**
 *	@file	device_memory.hpp
 *
 *	@brief	DeviceMemory クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_MEMORY_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_MEMORY_HPP

#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DeviceMemory
{
public:
	explicit DeviceMemory(
		DeviceSharedPtr const& device,
		::VkMemoryRequirements const& requirements,
		::VkFlags requirements_mask);

	~DeviceMemory();

	void* MapMemory(::VkDeviceSize size);

	void UnmapMemory(void);

	operator ::VkDeviceMemory() const;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkDeviceMemory			m_device_memory;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/device_memory_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEVICE_MEMORY_HPP
