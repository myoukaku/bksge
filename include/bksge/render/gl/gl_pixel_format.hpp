﻿/**
 *	@file	gl_pixel_format.hpp
 *
 *	@brief	ToGlPixelFormat の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_PIXEL_FORMAT_HPP
#define BKSGE_RENDER_GL_GL_PIXEL_FORMAT_HPP

#include <bksge/render/fwd/texture_format_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	TextureFormatをOpenGLのenumに変換
 */
GLenum ToGlPixelFormat(TextureFormat format);

GLint ToGlInternalPixelFormat(TextureFormat format);

GLenum ToGlPixelType(TextureFormat format);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_pixel_format_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_PIXEL_FORMAT_HPP