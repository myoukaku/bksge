/**
 *	@file	d3d11_depth_stencil_inl.hpp
 *
 *	@brief	D3D11DepthStencil の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_DEPTH_STENCIL_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_DEPTH_STENCIL_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_depth_stencil.hpp>
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11DepthStencil::D3D11DepthStencil(
	D3D11Device* device,
	::UINT       width,
	::UINT       height)
{
	::D3D11_TEXTURE2D_DESC desc_depth = {};
	desc_depth.Width              = width;
	desc_depth.Height             = height;
	desc_depth.MipLevels          = 1;
	desc_depth.ArraySize          = 1;
	desc_depth.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc_depth.SampleDesc.Count   = 1;
	desc_depth.SampleDesc.Quality = 0;
	desc_depth.Usage              = D3D11_USAGE_DEFAULT;
	desc_depth.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	desc_depth.CPUAccessFlags     = 0;
	desc_depth.MiscFlags          = 0;
	m_texture = device->CreateTexture2D(
		desc_depth,
		nullptr);

	// Create the depth stencil view
	::D3D11_DEPTH_STENCIL_VIEW_DESC desc_dsv = {};
	desc_dsv.Format             = desc_depth.Format;
	desc_dsv.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc_dsv.Texture2D.MipSlice = 0;
	m_view = device->CreateDepthStencilView(
		m_texture.Get(),
		&desc_dsv);
}

BKSGE_INLINE
D3D11DepthStencil::~D3D11DepthStencil()
{
}

BKSGE_INLINE ::ID3D11DepthStencilView*
D3D11DepthStencil::GetView(void) const
{
	return m_view.Get();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_DEPTH_STENCIL_INL_HPP
