/**
 *	@file	geometry_inl.hpp
 *
 *	@brief	Geometry クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_GEOMETRY_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_GEOMETRY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/geometry.hpp>
#include <bksge/render/d3d12/detail/vertex_buffer.hpp>
#include <bksge/render/d3d12/detail/index_buffer.hpp>
#include <bksge/render/d3d12/detail/command_list.hpp>
#include <bksge/render/d3d12/detail/primitive.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
Geometry::Geometry(bksge::Geometry const& geometry, Device* device)
	: m_vertex_buffer(new VertexBuffer(geometry, device))
	, m_index_buffer(new IndexBuffer(geometry, device))
	, m_primitive_topology(ToD3D12Primitive(geometry.primitive()))
{
}

BKSGE_INLINE
Geometry::~Geometry()
{
}

BKSGE_INLINE void
Geometry::Draw(CommandList* command_list)
{
	command_list->IASetPrimitiveTopology(m_primitive_topology);

	m_vertex_buffer->SetEnable(command_list);

	if (m_index_buffer->enable())
	{
		m_index_buffer->SetEnable(command_list);
		m_index_buffer->Draw(command_list);
	}
	else
	{
		m_vertex_buffer->Draw(command_list);
	}
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_GEOMETRY_INL_HPP
