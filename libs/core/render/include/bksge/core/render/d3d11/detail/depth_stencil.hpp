﻿/**
 *	@file	depth_stencil.hpp
 *
 *	@brief	DepthStencil クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_HPP

#include <bksge/core/render/d3d11/detail/fwd/depth_stencil_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class DepthStencil
{
public:
	explicit DepthStencil(
		Device*		device,
		::UINT      width,
		::UINT      height);

	~DepthStencil();

	::ID3D11DepthStencilView* GetView(void) const;

private:
	// noncopyable
	DepthStencil(DepthStencil const&) = delete;
	DepthStencil& operator=(DepthStencil const&) = delete;

private:
	ComPtr<ID3D11Texture2DN>         m_texture;
	ComPtr<::ID3D11DepthStencilView> m_view;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/depth_stencil_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_HPP
