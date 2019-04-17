/**
 *	@file	d3d11_wrap_mode_inl.hpp
 *
 *	@brief	D3D11WrapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_WRAP_MODE_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_WRAP_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_wrap_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d11_wrap_mode_detail
{

inline ::D3D11_TEXTURE_ADDRESS_MODE
ToD3D11WrapMode(WrapMode wrap_mode)
{
	switch (wrap_mode)
	{
	case WrapMode::kRepeat:  return D3D11_TEXTURE_ADDRESS_WRAP;
	case WrapMode::kClamp:   return D3D11_TEXTURE_ADDRESS_CLAMP;
	case WrapMode::kBorder:  return D3D11_TEXTURE_ADDRESS_BORDER;
	}
	return D3D11_TEXTURE_ADDRESS_CLAMP;
}

}	// namespace d3d11_wrap_mode_detail

BKSGE_INLINE
D3D11WrapMode::D3D11WrapMode(WrapMode wrap_mode)
	: m_wrap_mode(d3d11_wrap_mode_detail::ToD3D11WrapMode(wrap_mode))
{}

BKSGE_INLINE
D3D11WrapMode::operator D3D11_TEXTURE_ADDRESS_MODE() const
{
	return m_wrap_mode;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_WRAP_MODE_INL_HPP
