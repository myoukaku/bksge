/**
 *	@file	gl_texture_inl.hpp
 *
 *	@brief	GlTexture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_TEXTURE_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_TEXTURE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_texture.hpp>
#include <bksge/render/gl/gl_pixel_format.hpp>
#include <bksge/render/texture.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlTexture::GlTexture(Texture const& texture)
	: GlTexture(
		texture.format(),
		texture.width(),
		texture.height(),
		texture.data())
{}

BKSGE_INLINE
GlTexture::GlTexture(
	TextureFormat texture_format,
	int width,
	int height,
	void const* data)
{
	::glGenTextures(1, &m_name);

	Bind();

	GLint	const  level = 0;
	GLint	const  internal_format = ToGlInternalPixelFormat(texture_format);
	GLsizei	const  w = width;
	GLsizei	const  h = height;
	GLint	const  border = 0;
	GLenum	const  format = ToGlPixelFormat(texture_format);
	GLenum	const  type = ToGlPixelType(texture_format);
	GLvoid  const* p = data;
	::glTexImage2D(
		GL_TEXTURE_2D,
		level,
		internal_format,
		w,
		h,
		border,
		format,
		type,
		p);
}

BKSGE_INLINE
GlTexture::~GlTexture()
{
	::glDeleteTextures(1, &m_name);
}

BKSGE_INLINE
GLuint GlTexture::name(void) const
{
	return m_name;
}

BKSGE_INLINE
void GlTexture::Bind(void) const
{
	::glBindTexture(GL_TEXTURE_2D , m_name);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_TEXTURE_INL_HPP
