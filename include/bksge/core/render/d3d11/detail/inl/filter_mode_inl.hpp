/**
 *	@file	filter_mode_inl.hpp
 *
 *	@brief	FilterMode の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FILTER_MODE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FILTER_MODE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/filter_mode.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/filter_mode.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_FILTER_TYPE
ToD3D11FilterType(bksge::FilterMode filter)
{
	switch (filter)
	{
	case bksge::FilterMode::kNearest: return D3D11_FILTER_TYPE_POINT;
	case bksge::FilterMode::kLinear:  return D3D11_FILTER_TYPE_LINEAR;
	default:                          return D3D11_FILTER_TYPE_POINT;
	}
}

inline ::D3D11_FILTER_TYPE
ToD3D11FilterType(bksge::MipmapMode filter)
{
	switch (filter)
	{
	case bksge::MipmapMode::kNearest: return D3D11_FILTER_TYPE_POINT;
	case bksge::MipmapMode::kLinear:  return D3D11_FILTER_TYPE_LINEAR;
	default:                          return D3D11_FILTER_TYPE_POINT;
	}
}

}	// namespace detail

BKSGE_INLINE
FilterMode::FilterMode(
	bksge::FilterMode min_filter,
	bksge::FilterMode mag_filter,
	bksge::MipmapMode mip_filter)
	: m_filter(D3D11_ENCODE_BASIC_FILTER(
		detail::ToD3D11FilterType(min_filter),
		detail::ToD3D11FilterType(mag_filter),
		detail::ToD3D11FilterType(mip_filter),
		D3D11_FILTER_REDUCTION_TYPE_STANDARD))
{}

BKSGE_INLINE
FilterMode::operator ::D3D11_FILTER() const
{
	return m_filter;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_FILTER_MODE_INL_HPP
