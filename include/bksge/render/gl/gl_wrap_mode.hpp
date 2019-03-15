/**
 *	@file	gl_wrap_mode.hpp
 *
 *	@brief	ToGlWrapMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_WRAP_MODE_HPP
#define BKSGE_RENDER_GL_GL_WRAP_MODE_HPP

#include <bksge/render/fwd/wrap_mode_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	WrapModeをOpenGLのenumに変換
 */
GLint ToGlWrapMode(WrapMode mode);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_wrap_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_WRAP_MODE_HPP
