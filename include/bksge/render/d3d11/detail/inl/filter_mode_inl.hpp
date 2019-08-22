/**
 *	@file	filter_mode_inl.hpp
 *
 *	@brief	FilterMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_FILTER_MODE_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_FILTER_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/filter_mode.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_FILTER_TYPE
D3D11FilterType(bksge::FilterMode filter)
{
	switch (filter)
	{
	case bksge::FilterMode::kNearest: return D3D11_FILTER_TYPE_POINT;
	case bksge::FilterMode::kLinear:  return D3D11_FILTER_TYPE_LINEAR;
	}
	return D3D11_FILTER_TYPE_POINT;
}

}	// namespace detail

BKSGE_INLINE
FilterMode::FilterMode(bksge::FilterMode min_filter, bksge::FilterMode mag_filter)
	: m_filter(static_cast<::D3D11_FILTER>(
		(detail::D3D11FilterType(min_filter) << D3D11_MIN_FILTER_SHIFT) |
		(detail::D3D11FilterType(mag_filter) << D3D11_MAG_FILTER_SHIFT)))
{}

BKSGE_INLINE
FilterMode::operator ::D3D11_FILTER() const
{
	return m_filter;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_FILTER_MODE_INL_HPP
