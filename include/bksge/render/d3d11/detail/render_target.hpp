﻿/**
 *	@file	render_target.hpp
 *
 *	@brief	RenderTarget クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_RENDER_TARGET_HPP
#define BKSGE_RENDER_D3D11_DETAIL_RENDER_TARGET_HPP

#include <bksge/render/d3d11/detail/fwd/render_target_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class RenderTarget
{
public:
	RenderTarget(Device* device, DXGISwapChain* swap_chain);

	~RenderTarget();

	ComPtr<::ID3D11RenderTargetView> GetView(void) const;

private:
	ComPtr<::ID3D11RenderTargetView> m_view;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/render_target_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_RENDER_TARGET_HPP