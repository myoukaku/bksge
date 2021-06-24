/**
 *	@file	geometry_inl.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_GEOMETRY_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_GEOMETRY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/geometry.hpp>
#include <bksge/core/render/d3d11/detail/primitive_topology.hpp>
#include <bksge/core/render/d3d11/detail/device.hpp>
#include <bksge/core/render/d3d11/detail/device_context.hpp>
#include <bksge/core/render/geometry.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
Geometry::Geometry(
	Device* device,
	bksge::Geometry const& geometry)
	: m_vertex_buffer(device, geometry)
	, m_index_buffer(device, geometry)
	, m_primitive_topology(d3d11::PrimitiveTopology(geometry.primitive_topology()))
	, m_vertex_count(static_cast<::UINT>(geometry.vertex_array_count()))
	, m_index_count(static_cast<::UINT>(geometry.index_array_count()))
{}

BKSGE_INLINE
Geometry::~Geometry()
{}

BKSGE_INLINE void
Geometry::Draw(DeviceContext* device_context) const
{
	m_vertex_buffer.Bind(device_context);
	m_index_buffer.Bind(device_context);

	device_context->IASetPrimitiveTopology(m_primitive_topology);

	if (m_index_buffer.enable())
	{
		device_context->DrawIndexed(m_index_count, 0, 0);
	}
	else
	{
		device_context->Draw(m_vertex_count, 0);
	}
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_GEOMETRY_INL_HPP
