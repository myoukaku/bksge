/**
 *	@file	gl_filter_mode.hpp
 *
 *	@brief	ToGlFilterMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_FILTER_MODE_HPP
#define BKSGE_RENDER_GL_GL_FILTER_MODE_HPP

#include <bksge/render/fwd/filter_mode_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	FilterModeをOpenGLのenumに変換
 */
GLint ToGlFilterMode(FilterMode mode);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_filter_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_FILTER_MODE_HPP
