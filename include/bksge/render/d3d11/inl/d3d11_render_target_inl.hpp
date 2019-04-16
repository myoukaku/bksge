/**
 *	@file	d3d11_render_target_inl.hpp
 *
 *	@brief	D3D11RenderTarget の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_RENDER_TARGET_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_RENDER_TARGET_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_render_target.hpp>
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/dxgi/dxgi_swap_chain.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11RenderTarget::D3D11RenderTarget(
	D3D11Device* device,
	DXGISwapChain* swap_chain)
{
	ComPtr<::ID3D11Texture2D> back_buffer;
	swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));

	m_view = device->CreateRenderTargetView(
		back_buffer.Get(),
		nullptr);
}

BKSGE_INLINE
D3D11RenderTarget::~D3D11RenderTarget()
{
}

BKSGE_INLINE ComPtr<::ID3D11RenderTargetView>
D3D11RenderTarget::GetView(void) const
{
	return m_view;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_RENDER_TARGET_INL_HPP
