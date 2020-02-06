/**
 *	@file	color_write_flag_inl.hpp
 *
 *	@brief	ColorWriteFlag の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/color_write_flag.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/color_write_flag.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::UINT8
ToD3D11ColorWriteFlag(bksge::ColorWriteFlag color_write_flag)
{
	::UINT8 result = 0;

	if ((color_write_flag & bksge::ColorWriteFlag::kRed) != bksge::ColorWriteFlag::kNone)
	{
		result |= D3D11_COLOR_WRITE_ENABLE_RED;
	}
	if ((color_write_flag & bksge::ColorWriteFlag::kGreen) != bksge::ColorWriteFlag::kNone)
	{
		result |= D3D11_COLOR_WRITE_ENABLE_GREEN;
	}
	if ((color_write_flag & bksge::ColorWriteFlag::kBlue) != bksge::ColorWriteFlag::kNone)
	{
		result |= D3D11_COLOR_WRITE_ENABLE_BLUE;
	}
	if ((color_write_flag & bksge::ColorWriteFlag::kAlpha) != bksge::ColorWriteFlag::kNone)
	{
		result |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
	}

	return result;
}

}	// namespace detail

BKSGE_INLINE
ColorWriteFlag::ColorWriteFlag(bksge::ColorWriteFlag color_write_flag)
	: m_color_write_flag(detail::ToD3D11ColorWriteFlag(color_write_flag))
{}

BKSGE_INLINE
ColorWriteFlag::operator UINT8() const
{
	return m_color_write_flag;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_COLOR_WRITE_FLAG_INL_HPP
