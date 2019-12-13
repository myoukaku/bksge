/**
 *	@file	wrap_mode.hpp
 *
 *	@brief	WrapMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_WRAP_MODE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_WRAP_MODE_HPP

#include <bksge/core/render/fwd/wrap_mode_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	WrapModeをOpenGLのenumに変換
 */
class WrapMode
{
public:
	explicit WrapMode(bksge::WrapMode wrap_mode);

	operator ::GLint() const;

private:
	::GLint	m_wrap_mode;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/wrap_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_WRAP_MODE_HPP
