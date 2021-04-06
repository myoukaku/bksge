/**
 *	@file	buffer_object.hpp
 *
 *	@brief	BufferObject クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_OBJECT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_OBJECT_HPP

#include <bksge/core/render/vulkan/detail/fwd/buffer_object_fwd.hpp>
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

class BufferObject
{
public:
	explicit BufferObject(
		vulkan::DeviceSharedPtr const& device,
		::VkDeviceSize                 size,
		::VkBufferUsageFlags           usage,
		::VkFlags                      requirements_mask);

	~BufferObject();

	void* MapMemory(::VkDeviceSize size);

	void UnmapMemory(void);

	vulkan::Buffer const& buffer(void) const;

private:
	// noncopyable
	BufferObject(BufferObject const&) = delete;
	BufferObject& operator=(BufferObject const&) = delete;

private:
	vulkan::BufferUniquePtr			m_buffer;
	vulkan::DeviceMemoryUniquePtr	m_device_memory;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/buffer_object_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BUFFER_OBJECT_HPP
