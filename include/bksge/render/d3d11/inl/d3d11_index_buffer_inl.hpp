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
	: m_format(DXGI_FORMAT_UNKNOWN)
	, m_enable(false)
{
	auto const src = geometry.index_array_data();
	auto const size = geometry.index_array_bytes();
	auto const type = geometry.index_array_type();

	if (src != nullptr && size != 0u)
	{
		m_enable = true;
		m_format = ToD3D11Format(type);

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth           = static_cast<UINT>(size);
		desc.Usage               = D3D11_USAGE_DEFAULT;
		desc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags      = 0;
		desc.MiscFlags           = 0;
		desc.StructureByteStride = static_cast<UINT>(GetSizeOf(type));

		D3D11_SUBRESOURCE_DATA subsource_data;
		ZeroMemory(&subsource_data, sizeof(D3D11_SUBRESOURCE_DATA));
		subsource_data.pSysMem = src;

		m_buffer = renderer->CreateBuffer(desc, subsource_data);
	}
}

BKSGE_INLINE
D3D11IndexBuffer::~D3D11IndexBuffer()
{}

BKSGE_INLINE
void D3D11IndexBuffer::Bind(D3D11Renderer* renderer) const
{
	if (m_enable)
	{
		renderer->SetIndexBuffer(m_buffer.Get(), m_format, 0);
	}
}

BKSGE_INLINE bool
D3D11IndexBuffer::enable(void) const
{
	return m_enable;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_INDEX_BUFFER_INL_HPP
