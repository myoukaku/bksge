/**
 *	@file	buffer_object_inl.hpp
 *
 *	@brief	BufferObject クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_OBJECT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_OBJECT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/buffer_object.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
BufferObject::BufferObject(
	vulkan::DeviceSharedPtr const& device,
	::VkDeviceSize                 size,
	::VkBufferUsageFlags           usage,
	::VkFlags                      requirements_mask)
{
	m_buffer = bksge::make_unique<vulkan::Buffer>(
		device, size, usage);

	auto const mem_reqs = m_buffer->requirements();

	m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
		device, mem_reqs, requirements_mask);

	vk::BindBufferMemory(*device, *m_buffer, *m_device_memory, 0);
}

BKSGE_INLINE
BufferObject::~BufferObject()
{
}

BKSGE_INLINE void*
BufferObject::MapMemory(::VkDeviceSize size)
{
	return m_device_memory->MapMemory(size);
}

BKSGE_INLINE void
BufferObject::UnmapMemory(void)
{
	m_device_memory->UnmapMemory();
}

BKSGE_INLINE ::VkBuffer
BufferObject::GetBuffer(void) const
{
	return *m_buffer;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BUFFER_OBJECT_INL_HPP
