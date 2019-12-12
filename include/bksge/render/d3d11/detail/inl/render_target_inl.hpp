/**
 *	@file	render_target_inl.hpp
 *
 *	@brief	RenderTarget の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_RENDER_TARGET_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_RENDER_TARGET_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/render_target.hpp>
#include <bksge/render/d3d11/detail/device.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/dxgi/dxgi_swap_chain.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
RenderTarget::RenderTarget(
	Device* device,
	DXGISwapChain* swap_chain)
{
	ComPtr<::ID3D11Texture2D> back_buffer;
	swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));

	m_view = device->CreateRenderTargetView(
		back_buffer.Get(),
		nullptr);
}

BKSGE_INLINE
RenderTarget::~RenderTarget()
{
}

BKSGE_INLINE ComPtr<::ID3D11RenderTargetView> const&
RenderTarget::GetView(void) const
{
	return m_view;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_RENDER_TARGET_INL_HPP
