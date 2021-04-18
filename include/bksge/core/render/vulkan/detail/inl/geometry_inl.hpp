/**
 *	@file	geometry_inl.hpp
 *
 *	@brief	Geometry クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GEOMETRY_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GEOMETRY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/geometry.hpp>
#include <bksge/core/render/vulkan/detail/vertex_buffer.hpp>
#include <bksge/core/render/vulkan/detail/index_buffer.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Geometry::Geometry(vulkan::DeviceSharedPtr const& device, bksge::Geometry const& geometry)
	: m_vertex_buffer(new VertexBuffer(device, geometry))
	, m_index_buffer(new IndexBuffer(device, geometry))
{
}

BKSGE_INLINE
Geometry::~Geometry()
{
}

BKSGE_INLINE void
Geometry::Draw(vulkan::CommandBuffer* command_buffer)
{
	if (m_index_buffer->enable())
	{
		m_vertex_buffer->Bind(command_buffer);
		m_index_buffer->Bind(command_buffer);
		m_index_buffer->Draw(command_buffer);
	}
	else
	{
		m_vertex_buffer->Bind(command_buffer);
		m_vertex_buffer->Draw(command_buffer);
	}
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GEOMETRY_INL_HPP
