/**
 *	@file	wrap_mode_inl.hpp
 *
 *	@brief	WrapMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_WRAP_MODE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_WRAP_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/wrap_mode.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/wrap_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_TEXTURE_ADDRESS_MODE
ToD3D12WrapMode(bksge::WrapMode wrap_mode)
{
	switch (wrap_mode)
	{
	case bksge::WrapMode::kRepeat:  return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	case bksge::WrapMode::kClamp:   return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	case bksge::WrapMode::kBorder:  return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	}
	return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
}

}	// namespace detail

BKSGE_INLINE
WrapMode::WrapMode(bksge::WrapMode wrap_mode)
	: m_wrap_mode(detail::ToD3D12WrapMode(wrap_mode))
{}

BKSGE_INLINE
WrapMode::operator D3D12_TEXTURE_ADDRESS_MODE() const
{
	return m_wrap_mode;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_WRAP_MODE_INL_HPP
