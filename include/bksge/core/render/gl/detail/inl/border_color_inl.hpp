/**
 *	@file	border_color_inl.hpp
 *
 *	@brief	BorderColor クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_BORDER_COLOR_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_BORDER_COLOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/border_color.hpp>
#include <bksge/core/render/border_color.hpp>

namespace bksge
{

namespace render
{

namespace gl
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

BKSGE_INLINE ::GLfloat
BorderColor::operator[](std::size_t i) const
{
	return m_border_color[i];
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_BORDER_COLOR_INL_HPP
