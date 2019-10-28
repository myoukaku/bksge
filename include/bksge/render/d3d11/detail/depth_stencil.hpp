﻿/**
 *	@file	depth_stencil.hpp
 *
 *	@brief	DepthStencil クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_HPP

#include <bksge/render/d3d11/detail/fwd/depth_stencil_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

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
	DepthStencil(
		Device*		device,
		::UINT      width,
		::UINT      height);

	~DepthStencil();

	::ID3D11DepthStencilView* GetView(void) const;

private:
	ComPtr<::ID3D11Texture2D>        m_texture;
	ComPtr<::ID3D11DepthStencilView> m_view;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/detail/inl/depth_stencil_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_HPP