/**
 *	@file	d3d12_geometry_inl.hpp
 *
 *	@brief	D3D12Geometry クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_GEOMETRY_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_GEOMETRY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_geometry.hpp>
#include <bksge/render/d3d12/d3d12_vertex_buffer.hpp>
#include <bksge/render/d3d12/d3d12_index_buffer.hpp>
#include <bksge/render/d3d12/d3d12_command_list.hpp>
#include <bksge/render/d3d12/d3d12_primitive.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12Geometry::D3D12Geometry(Geometry const& geometry, D3D12Device* device)
	: m_vertex_buffer(new D3D12VertexBuffer(geometry, device))
	, m_index_buffer(new D3D12IndexBuffer(geometry, device))
	, m_primitive_topology(ToD3D12Primitive(geometry.primitive()))
{
}

BKSGE_INLINE
D3D12Geometry::~D3D12Geometry()
{
}

BKSGE_INLINE void
D3D12Geometry::Draw(D3D12CommandList* command_list)
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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_GEOMETRY_INL_HPP
