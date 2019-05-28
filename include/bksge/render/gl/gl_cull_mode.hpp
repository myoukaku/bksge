/**
 *	@file	gl_cull_mode.hpp
 *
 *	@brief	ToGlCullMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_CULL_MODE_HPP
#define BKSGE_RENDER_GL_GL_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	CullModeをOpenGLのenumに変換
 */
GLenum ToGlCullMode(CullMode cull_mode);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_cull_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_CULL_MODE_HPP
