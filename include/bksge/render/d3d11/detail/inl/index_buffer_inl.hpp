/**
 *	@file	index_buffer_inl.hpp
 *
 *	@brief	IndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_INDEX_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_INDEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/index_buffer.hpp>
#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/d3d11/detail/device_context.hpp>
#include <bksge/render/d3d11/detail/type_enum.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/dxgiformat.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
IndexBuffer::IndexBuffer(
	Device* device,
	bksge::Geometry const& geometry)
	: m_format(DXGI_FORMAT_UNKNOWN)
	, m_enable(false)
{
	auto const src  = geometry.index_array_data();
	auto const size = geometry.index_array_bytes();
	auto const type = geometry.index_array_type();

	if (src != nullptr && size != 0u)
	{
		m_enable = true;
		m_format = d3d11::TypeEnum(type);

		::D3D11_BUFFER_DESC desc;
		desc.ByteWidth           = static_cast<::UINT>(size);
		desc.Usage               = D3D11_USAGE_DEFAULT;
		desc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags      = 0;
		desc.MiscFlags           = 0;
		desc.StructureByteStride = static_cast<::UINT>(GetSizeOf(type));

		::D3D11_SUBRESOURCE_DATA subsource_data;
		ZeroMemory(&subsource_data, sizeof(::D3D11_SUBRESOURCE_DATA));
		subsource_data.pSysMem = src;

		m_buffer = device->CreateBuffer(desc, &subsource_data);
	}
}

BKSGE_INLINE
IndexBuffer::~IndexBuffer()
{}

BKSGE_INLINE
void IndexBuffer::Bind(DeviceContext* device_context) const
{
	if (m_enable)
	{
		device_context->IASetIndexBuffer(m_buffer.Get(), m_format, 0);
	}
}

BKSGE_INLINE bool
IndexBuffer::enable(void) const
{
	return m_enable;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_INDEX_BUFFER_INL_HPP
