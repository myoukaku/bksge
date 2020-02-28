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
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

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
		texture.mipmap_count(),
		texture.data())
{}

BKSGE_INLINE
Texture::Texture(
	bksge::TextureFormat texture_format,
	std::uint32_t width,
	std::uint32_t height,
	bksge::size_t mipmap_count,
	std::uint8_t const* data)
{
	::glGenTextures(1, &m_name);

	::glBindTexture(GL_TEXTURE_2D , m_name);

	::GLint	  const  internal_format = ToGlInternalPixelFormat(texture_format);
	::GLenum  const  format = ToGlPixelFormat(texture_format);
	::GLenum  const  type = ToGlPixelType(texture_format);

	for (bksge::size_t level = 0; level < mipmap_count; ++level)
	{
		::glTexImage2D(
			GL_TEXTURE_2D,
			static_cast<::GLint>(level),
			internal_format,
			static_cast<::GLsizei>(width),
			static_cast<::GLsizei>(height),
			0,	// must be 0
			format,
			type,
			static_cast<const void*>(data));

		data += GetSizeInBytes(texture_format, width, height);
		width  = bksge::max(width  / 2, 1u);
		height = bksge::max(height / 2, 1u);
	}

	::glBindTexture(GL_TEXTURE_2D , 0);
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
Texture::Bind(GLint location) const
{
	::glUniform1i(location, location);
	::glActiveTexture(GL_TEXTURE0 + location);
	::glBindTexture(GL_TEXTURE_2D , m_name);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_TEXTURE_INL_HPP
