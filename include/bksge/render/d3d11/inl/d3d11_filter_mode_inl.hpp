/**
 *	@file	d3d11_filter_mode_inl.hpp
 *
 *	@brief	D3D11FilterMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_FILTER_MODE_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_FILTER_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_filter_mode.hpp>

namespace bksge
{

namespace render
{

namespace detail
{

inline ::D3D11_FILTER_TYPE
D3D11FilterType(FilterMode filter)
{
	switch (filter)
	{
	case FilterMode::kNearest: return D3D11_FILTER_TYPE_POINT;
	case FilterMode::kLinear:  return D3D11_FILTER_TYPE_LINEAR;
	}
	return D3D11_FILTER_TYPE_POINT;
}

}	// namespace detail

BKSGE_INLINE
D3D11FilterMode::D3D11FilterMode(FilterMode min_filter, FilterMode mag_filter)
	: m_filter(static_cast<::D3D11_FILTER>(
		(detail::D3D11FilterType(min_filter) << D3D11_MIN_FILTER_SHIFT) |
		(detail::D3D11FilterType(mag_filter) << D3D11_MAG_FILTER_SHIFT)))
{}

BKSGE_INLINE
D3D11FilterMode::operator ::D3D11_FILTER() const
{
	return m_filter;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_FILTER_MODE_INL_HPP
