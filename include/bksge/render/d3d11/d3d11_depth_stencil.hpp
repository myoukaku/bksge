/**
 *	@file	d3d11_depth_stencil.hpp
 *
 *	@brief	D3D11DepthStencil クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_DEPTH_STENCIL_HPP
#define BKSGE_RENDER_D3D11_D3D11_DEPTH_STENCIL_HPP

#include <bksge/render/d3d11/fwd/d3d11_depth_stencil_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11DepthStencil
{
public:
	D3D11DepthStencil(
		D3D11Device* device,
		::UINT       width,
		::UINT       height);

	~D3D11DepthStencil();

	::ID3D11DepthStencilView* GetView(void) const;

private:
	ComPtr<::ID3D11Texture2D>        m_texture;
	ComPtr<::ID3D11DepthStencilView> m_view;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_depth_stencil_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_DEPTH_STENCIL_HPP
