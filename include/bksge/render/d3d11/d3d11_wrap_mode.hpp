/**
 *	@file	d3d11_wrap_mode.hpp
 *
 *	@brief	D3D11WrapMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_WRAP_MODE_HPP
#define BKSGE_RENDER_D3D11_D3D11_WRAP_MODE_HPP

#include <bksge/render/wrap_mode.hpp>
#include <bksge/render/d3d11/d3d11.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11WrapMode
{
public:
	D3D11WrapMode(WrapMode wrap_mode);

	operator D3D11_TEXTURE_ADDRESS_MODE() const;

private:
	D3D11_TEXTURE_ADDRESS_MODE	m_wrap_mode;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_wrap_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_WRAP_MODE_HPP
