/**
 *	@file	wrap_mode_inl.hpp
 *
 *	@brief	WrapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_WRAP_MODE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_WRAP_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/wrap_mode.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/wrap_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_TEXTURE_ADDRESS_MODE
ToD3D11WrapMode(bksge::WrapMode wrap_mode)
{
	switch (wrap_mode)
	{
	case bksge::WrapMode::kRepeat:  return D3D11_TEXTURE_ADDRESS_WRAP;
	case bksge::WrapMode::kClamp:   return D3D11_TEXTURE_ADDRESS_CLAMP;
	case bksge::WrapMode::kBorder:  return D3D11_TEXTURE_ADDRESS_BORDER;
	}
	return D3D11_TEXTURE_ADDRESS_CLAMP;
}

}	// namespace detail

BKSGE_INLINE
WrapMode::WrapMode(bksge::WrapMode wrap_mode)
	: m_wrap_mode(detail::ToD3D11WrapMode(wrap_mode))
{}

BKSGE_INLINE
WrapMode::operator D3D11_TEXTURE_ADDRESS_MODE() const
{
	return m_wrap_mode;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_WRAP_MODE_INL_HPP
