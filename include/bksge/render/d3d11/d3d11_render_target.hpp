/**
 *	@file	d3d11_render_target.hpp
 *
 *	@brief	D3D11RenderTarget クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_RENDER_TARGET_HPP
#define BKSGE_RENDER_D3D11_D3D11_RENDER_TARGET_HPP

#include <bksge/render/d3d11/fwd/d3d11_render_target_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11RenderTarget
{
public:
	D3D11RenderTarget(D3D11Device* device, DXGISwapChain* swap_chain);

	~D3D11RenderTarget();

	ComPtr<::ID3D11RenderTargetView> GetView(void) const;

private:
	ComPtr<::ID3D11RenderTargetView> m_view;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_render_target_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_RENDER_TARGET_HPP
