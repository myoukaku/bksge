/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_BORDER_COLOR_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_BORDER_COLOR_HPP

#include <bksge/core/render/border_color.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class BorderColor
{
public:
	explicit BorderColor(bksge::BorderColor border_color);

	::FLOAT operator[](bksge::size_t i) const;

private:
	::FLOAT	m_border_color[4];
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/border_color_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_BORDER_COLOR_HPP
