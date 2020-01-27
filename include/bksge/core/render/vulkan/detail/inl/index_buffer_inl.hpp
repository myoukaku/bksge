/**
 *	@file	index_buffer_inl.hpp
 *
 *	@brief	IndexBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INDEX_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INDEX_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/index_buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/index_type.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <cstring>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
IndexBuffer::IndexBuffer(
	vulkan::DeviceSharedPtr const& device,
	bksge::Geometry const& geometry)
{
	auto const src  = geometry.index_array_data();
	auto const size = geometry.index_array_bytes();

	if (src == nullptr || size == 0u)
	{
		return;
	}

	m_count = static_cast<std::uint32_t>(geometry.index_array_count());
	m_type  = vulkan::IndexType(geometry.index_array_type());

	m_buffer = bksge::make_unique<Buffer>(
		device,
		size,
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT);

	auto const mem_reqs = m_buffer->requirements();

	m_device_memory = bksge::make_unique<DeviceMemory>(
		device,
		mem_reqs,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	vk::BindBufferMemory(*device, *m_buffer, *m_device_memory, 0);

	{
		void* dst;
		vk::MapMemory(*device, *m_device_memory, 0, size, 0, &dst);
		std::memcpy(dst, src, size);
		vk::UnmapMemory(*device, *m_device_memory);
	}
}

BKSGE_INLINE
IndexBuffer::~IndexBuffer()
{
}

BKSGE_INLINE void
IndexBuffer::Bind(CommandBuffer* command_buffer)
{
	vk::CmdBindIndexBuffer(*command_buffer, *m_buffer, 0, m_type);
}

BKSGE_INLINE void
IndexBuffer::Draw(CommandBuffer* command_buffer)
{
	vk::CmdDrawIndexed(*command_buffer, m_count, 1, 0, 0, 0);
}

BKSGE_INLINE bool
IndexBuffer::enable(void) const
{
	return m_count != 0;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_INDEX_BUFFER_INL_HPP
