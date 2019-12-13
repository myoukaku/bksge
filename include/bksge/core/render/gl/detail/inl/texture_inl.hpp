/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/pixel_format.hpp>
#include <bksge/core/render/texture.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
Texture::Texture(bksge::Texture const& texture)
	: Texture(
		texture.format(),
		texture.width(),
		texture.height(),
		texture.data())
{}

BKSGE_INLINE
Texture::Texture(
	bksge::TextureFormat texture_format,
	int width,
	int height,
	void const* data)
{
	::glGenTextures(1, &m_name);

	Bind();

	::GLint	  const  level = 0;
	::GLint	  const  internal_format = ToGlInternalPixelFormat(texture_format);
	::GLsizei const  w = width;
	::GLsizei const  h = height;
	::GLint	  const  border = 0;
	::GLenum  const  format = ToGlPixelFormat(texture_format);
	::GLenum  const  type = ToGlPixelType(texture_format);
	::GLvoid  const* p = data;
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
Texture::~Texture()
{
	::glDeleteTextures(1, &m_name);
}

BKSGE_INLINE ::GLuint
Texture::name(void) const
{
	return m_name;
}

BKSGE_INLINE void
Texture::Bind(void) const
{
	::glBindTexture(GL_TEXTURE_2D , m_name);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_TEXTURE_INL_HPP
