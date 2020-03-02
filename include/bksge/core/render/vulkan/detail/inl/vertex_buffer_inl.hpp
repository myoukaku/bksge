﻿/**
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
#include <bksge/core/render/vulkan/detail/buffer_object.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
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
	m_count = static_cast<bksge::uint32_t>(geometry.vertex_array_count());
	auto const src  = geometry.vertex_array_data();
	auto const size = geometry.vertex_array_bytes();

	m_buffer = bksge::make_unique<vulkan::BufferObject>(
		device,
		size,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	{
		void* dst = m_buffer->MapMemory(size);
		std::memcpy(dst, src, size);
		m_buffer->UnmapMemory();
	}
}

BKSGE_INLINE
VertexBuffer::~VertexBuffer()
{
}

BKSGE_INLINE void
VertexBuffer::Bind(vulkan::CommandBuffer* command_buffer)
{
	::VkBuffer buffer = m_buffer->GetBuffer();
	::VkDeviceSize offset = 0;
	vk::CmdBindVertexBuffers(
		*command_buffer,
		0,
		1,
		&buffer,
		&offset);
}

BKSGE_INLINE void
VertexBuffer::Draw(vulkan::CommandBuffer* command_buffer)
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
