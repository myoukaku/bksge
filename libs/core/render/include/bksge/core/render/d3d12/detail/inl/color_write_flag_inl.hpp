/**
 *	@file	color_write_flag_inl.hpp
 *
 *	@brief	ColorWriteFlag の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/color_write_flag.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/color_write_flag.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::UINT8
ToD3D12ColorWriteFlag(bksge::ColorWriteFlag color_write_flag)
{
	::UINT8 result = 0;

	if (Test(color_write_flag, bksge::ColorWriteFlag::kRed))
	{
		result |= D3D12_COLOR_WRITE_ENABLE_RED;
	}
	if (Test(color_write_flag, bksge::ColorWriteFlag::kGreen))
	{
		result |= D3D12_COLOR_WRITE_ENABLE_GREEN;
	}
	if (Test(color_write_flag, bksge::ColorWriteFlag::kBlue))
	{
		result |= D3D12_COLOR_WRITE_ENABLE_BLUE;
	}
	if (Test(color_write_flag, bksge::ColorWriteFlag::kAlpha))
	{
		result |= D3D12_COLOR_WRITE_ENABLE_ALPHA;
	}

	return result;
}

}	// namespace detail

BKSGE_INLINE
ColorWriteFlag::ColorWriteFlag(bksge::ColorWriteFlag color_write_flag)
	: m_color_write_flag(detail::ToD3D12ColorWriteFlag(color_write_flag))
{}

BKSGE_INLINE
ColorWriteFlag::operator UINT8() const
{
	return m_color_write_flag;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP
