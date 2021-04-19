/**
 *	@file	buffer.hpp
 *
 *	@brief	Buffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_memory_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Buffer
{
public:
	explicit Buffer(
		vulkan::DeviceSharedPtr const& device,
		::VkDeviceSize                 size,
		::VkBufferUsageFlags           usage,
		::VkFlags                      requirements_mask);

	~Buffer();

	void* MapMemory(::VkDeviceSize size);

	void UnmapMemory(void);

	::VkBuffer const* GetAddressOf(void) const;

private:
	// noncopyable
	Buffer(Buffer const&) = delete;
	Buffer& operator=(Buffer const&) = delete;

private:
	::VkBuffer						m_buffer;
	vulkan::DeviceSharedPtr			m_device;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_HPP
