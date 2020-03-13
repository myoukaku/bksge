/**
 *	@file	border_color_inl.hpp
 *
 *	@brief	BorderColor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BORDER_COLOR_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BORDER_COLOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/border_color.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/border_color.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
BorderColor::BorderColor(bksge::BorderColor border_color)
{
	switch (border_color)
	{
	case bksge::BorderColor::kTransparentBlack:
		m_border_color[0] = 0;
		m_border_color[1] = 0;
		m_border_color[2] = 0;
		m_border_color[3] = 0;
		break;
	case bksge::BorderColor::kOpaqueBlack:
		m_border_color[0] = 0;
		m_border_color[1] = 0;
		m_border_color[2] = 0;
		m_border_color[3] = 1;
		break;
	case bksge::BorderColor::kOpaqueWhite:
		m_border_color[0] = 1;
		m_border_color[1] = 1;
		m_border_color[2] = 1;
		m_border_color[3] = 1;
		break;
	}
}

BKSGE_INLINE ::FLOAT
BorderColor::operator[](std::size_t i) const
{
	return m_border_color[i];
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BORDER_COLOR_INL_HPP
