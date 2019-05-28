/**
 *	@file	gl_fill_mode.hpp
 *
 *	@brief	ToGlFillMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_FILL_MODE_HPP
#define BKSGE_RENDER_GL_GL_FILL_MODE_HPP

#include <bksge/render/fwd/fill_mode_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	FillModeをOpenGLのenumに変換
 */
GLenum ToGlFillMode(FillMode fill_mode);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_fill_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_FILL_MODE_HPP
