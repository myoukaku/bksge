/**
 *	@file	render_target.hpp
 *
 *	@brief	RenderTarget クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_RENDER_TARGET_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_RENDER_TARGET_HPP

#include <bksge/core/render/d3d11/detail/fwd/render_target_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>

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
	explicit RenderTarget(Device* device, DXGISwapChain* swap_chain);

	~RenderTarget();

	::ID3D11RenderTargetView* GetView(void) const;

private:
	// noncopyable
	RenderTarget(RenderTarget const&) = delete;
	RenderTarget& operator=(RenderTarget const&) = delete;

private:
	ComPtr<ID3D11RenderTargetViewN> m_view;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/render_target_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_RENDER_TARGET_HPP
