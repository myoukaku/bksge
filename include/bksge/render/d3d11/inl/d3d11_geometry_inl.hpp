/**
 *	@file	d3d11_geometry_inl.hpp
 *
 *	@brief	D3D11Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_GEOMETRY_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_GEOMETRY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_geometry.hpp>
#include <bksge/render/d3d11/d3d11_primitive.hpp>
#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11Geometry::D3D11Geometry(
	D3D11Renderer* renderer,
	Geometry const& geometry)
	: m_vertex_buffer(renderer, geometry)
	, m_index_buffer(renderer, geometry)
	, m_primitive(ToD3D11Primitive(geometry.primitive()))
	, m_vertex_count(static_cast<UINT>(geometry.vertex_array_count()))
	, m_index_count(static_cast<UINT>(geometry.index_array_count()))
{}

BKSGE_INLINE
D3D11Geometry::~D3D11Geometry()
{}

BKSGE_INLINE
void D3D11Geometry::Draw(D3D11Renderer* renderer) const
{
	m_vertex_buffer.Bind(renderer);
	m_index_buffer.Bind(renderer);

	renderer->SetPrimitiveTopology(m_primitive);
	if (m_index_buffer.enable())
	{
		renderer->DrawIndexed(m_index_count, 0, 0);
	}
	else
	{
		renderer->Draw(m_vertex_count, 0);
	}
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_GEOMETRY_INL_HPP
