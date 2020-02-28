/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_BORDER_COLOR_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_BORDER_COLOR_HPP

#include <bksge/core/render/fwd/border_color_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	BorderColorをOpenGLのenumに変換
 */
class BorderColor
{
public:
	explicit BorderColor(bksge::BorderColor border_color);

	operator ::GLfloat const*() const;

private:
	::GLfloat	m_border_color[4];
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/border_color_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_BORDER_COLOR_HPP
