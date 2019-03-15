/**
 *	@file	d3d11_index_buffer_inl.hpp
 *
 *	@brief	D3D11IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_INDEX_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_INDEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_index_buffer.hpp>
#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/d3d11/d3d11_format.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d11/com_ptr.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11IndexBuffer::D3D11IndexBuffer(
	D3D11Renderer* renderer,
	Geometry const& geometry)
	: m_format(ToD3D11Format(geometry.index_array_type()))
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth           = static_cast<UINT>(geometry.index_array_bytes());
	desc.Usage               = D3D11_USAGE_DEFAULT;
	desc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags      = 0;
	desc.MiscFlags           = 0;
	desc.StructureByteStride = static_cast<UINT>(GetSizeOf(geometry.index_array_type()));

	D3D11_SUBRESOURCE_DATA subsource_data;
	ZeroMemory(&subsource_data, sizeof(D3D11_SUBRESOURCE_DATA));
	subsource_data.pSysMem = geometry.index_array_data();

	m_buffer = renderer->CreateBuffer(desc, subsource_data);
}

BKSGE_INLINE
D3D11IndexBuffer::~D3D11IndexBuffer()
{}

BKSGE_INLINE
void D3D11IndexBuffer::Bind(D3D11Renderer* renderer) const
{
	renderer->SetIndexBuffer(m_buffer.Get(), m_format, 0);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_INDEX_BUFFER_INL_HPP
