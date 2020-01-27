/**
 *	@file	vertex_buffer_inl.hpp
 *
 *	@brief	VertexBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VERTEX_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VERTEX_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/vertex_buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/buffer.hpp>
#include <bksge/core/render/vulkan/detail/device_memory.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
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
VertexBuffer::VertexBuffer(
	vulkan::DeviceSharedPtr const& device,
	bksge::Geometry const& geometry)
{
	m_count = static_cast<std::uint32_t>(geometry.vertex_array_count());
	auto const src  = geometry.vertex_array_data();
	auto const size = geometry.vertex_array_bytes();

	m_buffer = bksge::make_unique<vulkan::Buffer>(
		device,
		size,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

	auto const mem_reqs = m_buffer->requirements();

	m_device_memory = bksge::make_unique<vulkan::DeviceMemory>(
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
VertexBuffer::~VertexBuffer()
{
}

BKSGE_INLINE void
VertexBuffer::Bind(CommandBuffer* command_buffer)
{
	::VkDeviceSize offset = 0;
	vk::CmdBindVertexBuffers(
		*command_buffer,
		0,
		1,
		m_buffer->GetAddressOf(),
		&offset);
}

BKSGE_INLINE void
VertexBuffer::Draw(CommandBuffer* command_buffer)
{
	vk::CmdDraw(
		*command_buffer,
		m_count,
		1,
		0,
		0);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VERTEX_BUFFER_INL_HPP
