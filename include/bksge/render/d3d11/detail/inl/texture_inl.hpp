/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_TEXTURE_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_TEXTURE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/texture.hpp>
#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/texture.hpp>
#include <bksge/assert.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::DXGI_FORMAT
ToDXGIPixelFormat(bksge::TextureFormat format)
{
	// TODO
	(void)format;
	return DXGI_FORMAT_R8G8B8A8_UNORM;
}

}	// namespace detail

BKSGE_INLINE
Texture::Texture(Device* device, bksge::Texture const& texture)
{
	::D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width              = texture.width();
	desc.Height             = texture.height();
	desc.MipLevels          = 1;
	desc.ArraySize          = 1;
	desc.Format             = detail::ToDXGIPixelFormat(texture.format());
	desc.SampleDesc.Count   = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage              = D3D11_USAGE_DEFAULT;
	desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags     = 0;
	desc.MiscFlags          = 0;

	::D3D11_SUBRESOURCE_DATA init_data {};
	init_data.pSysMem          = texture.data();
	init_data.SysMemPitch      = static_cast<::UINT>(texture.stride());
	init_data.SysMemSlicePitch = static_cast<::UINT>(texture.stride());

	m_texture = device->CreateTexture2D(desc, &init_data);

	{
		::D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc {};
		srv_desc.Format                    = desc.Format;
		srv_desc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2D.MostDetailedMip = 0;
		srv_desc.Texture2D.MipLevels       = desc.MipLevels;

		m_shader_resource_view =
			device->CreateShaderResourceView(m_texture.Get(), srv_desc);
	}
}

BKSGE_INLINE
Texture::~Texture()
{
}

BKSGE_INLINE ::ID3D11Texture2D*
Texture::texture() const
{
	return m_texture.Get();
}

BKSGE_INLINE ::ID3D11ShaderResourceView*
Texture::shader_resource_view() const
{
	return m_shader_resource_view.Get();
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_TEXTURE_INL_HPP
