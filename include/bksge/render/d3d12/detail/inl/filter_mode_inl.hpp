/**
 *	@file	filter_mode_inl.hpp
 *
 *	@brief	FilterMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_FILTER_MODE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_FILTER_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/filter_mode.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/filter_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_FILTER_TYPE
D3D12FilterType(bksge::FilterMode filter)
{
	switch (filter)
	{
	case bksge::FilterMode::kNearest: return D3D12_FILTER_TYPE_POINT;
	case bksge::FilterMode::kLinear:  return D3D12_FILTER_TYPE_LINEAR;
	}
	return D3D12_FILTER_TYPE_POINT;
}

}	// namespace detail

BKSGE_INLINE
FilterMode::FilterMode(bksge::FilterMode min_filter, bksge::FilterMode mag_filter)
	: m_filter(static_cast<::D3D12_FILTER>(
		(detail::D3D12FilterType(min_filter) << D3D12_MIN_FILTER_SHIFT) |
		(detail::D3D12FilterType(mag_filter) << D3D12_MAG_FILTER_SHIFT)))
{}

BKSGE_INLINE
FilterMode::operator ::D3D12_FILTER() const
{
	return m_filter;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_FILTER_MODE_INL_HPP
