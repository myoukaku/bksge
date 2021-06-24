/**
 *	@file	render_target_inl.hpp
 *
 *	@brief	RenderTarget の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RENDER_TARGET_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RENDER_TARGET_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/render_target.hpp>
#include <bksge/core/render/d3d11/detail/device.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/dxgi/dxgi_swap_chain.hpp>

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
		static_cast<D3D11_RENDER_TARGET_VIEW_DESC_N*>(nullptr));
}

BKSGE_INLINE
RenderTarget::~RenderTarget()
{
}

BKSGE_INLINE ::ID3D11RenderTargetView*
RenderTarget::GetView(void) const
{
	return m_view.Get();
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RENDER_TARGET_INL_HPP
