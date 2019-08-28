/**
 *	@file	pixel_format.hpp
 *
 *	@brief	ToGlPixelFormat の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_PIXEL_FORMAT_HPP
#define BKSGE_RENDER_GL_DETAIL_PIXEL_FORMAT_HPP

#include <bksge/render/fwd/texture_format_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	TextureFormatをOpenGLのenumに変換
 */
::GLenum ToGlPixelFormat(bksge::TextureFormat format);

::GLint ToGlInternalPixelFormat(bksge::TextureFormat format);

::GLenum ToGlPixelType(bksge::TextureFormat format);

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/pixel_format_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_PIXEL_FORMAT_HPP
