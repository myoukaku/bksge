/**
 *	@file	d3d11_vertex_buffer_inl.hpp
 *
 *	@brief	D3D11VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_VERTEX_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_VERTEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_vertex_buffer.hpp>
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d11/d3d11_device_context.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/vertex_layout.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11VertexBuffer::D3D11VertexBuffer(
	D3D11Device* device,
	Geometry const& geometry)
	: m_stride(static_cast<::UINT>(geometry.vertex_layout().total_bytes()))
{
	::D3D11_BUFFER_DESC desc;
	desc.ByteWidth      = static_cast<::UINT>(geometry.vertex_array_bytes());
	desc.Usage          = D3D11_USAGE_DEFAULT;
	desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags      = 0;

	::D3D11_SUBRESOURCE_DATA subsource_data;
	ZeroMemory(&subsource_data, sizeof(::D3D11_SUBRESOURCE_DATA));
	subsource_data.pSysMem = geometry.vertex_array_data();

	m_buffer = device->CreateBuffer(desc, subsource_data);
}

BKSGE_INLINE
D3D11VertexBuffer::~D3D11VertexBuffer()
{
}

BKSGE_INLINE void
D3D11VertexBuffer::Bind(D3D11DeviceContext* device_context) const
{
	device_context->IASetVertexBuffers(0, 1, m_buffer.GetAddressOf(), &m_stride, &m_offset);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_VERTEX_BUFFER_INL_HPP
