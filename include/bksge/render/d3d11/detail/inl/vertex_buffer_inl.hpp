/**
 *	@file	vertex_buffer_inl.hpp
 *
 *	@brief	VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_VERTEX_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_VERTEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/vertex_buffer.hpp>
#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/d3d11/detail/device_context.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/vertex_layout.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
VertexBuffer::VertexBuffer(
	Device* device,
	bksge::Geometry const& geometry)
	: m_stride(static_cast<::UINT>(geometry.vertex_layout().total_bytes()))
{
	::D3D11_BUFFER_DESC desc;
	desc.ByteWidth      = static_cast<::UINT>(geometry.vertex_array_bytes());
	desc.Usage          = D3D11_USAGE_DEFAULT;
	desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags      = 0;

	::D3D11_SUBRESOURCE_DATA subsource_data {};
	subsource_data.pSysMem = geometry.vertex_array_data();

	m_buffer = device->CreateBuffer(desc, &subsource_data);
}

BKSGE_INLINE
VertexBuffer::~VertexBuffer()
{
}

BKSGE_INLINE void
VertexBuffer::Bind(DeviceContext* device_context) const
{
	device_context->IASetVertexBuffers(0, 1, m_buffer.GetAddressOf(), &m_stride, &m_offset);
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_VERTEX_BUFFER_INL_HPP
