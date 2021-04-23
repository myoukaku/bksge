/**
 *	@file	render_buffer_inl.hpp
 *
 *	@brief	RenderBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/render_buffer.hpp>
#include <bksge/core/render/gl/detail/pixel_format.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/core/render/render_texture.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
RenderBuffer::RenderBuffer(
	bksge::TextureFormat texture_format,
	bksge::uint32_t width,
	bksge::uint32_t height)
{
	::glGenRenderbuffers(1, &m_id);
	Bind();

	::GLint const  internal_format = ToGlInternalPixelFormat(texture_format);
	::glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
}

BKSGE_INLINE
RenderBuffer::RenderBuffer(bksge::RenderTexture const& texture)
	: RenderBuffer(
		texture.format(),
		texture.extent().width(),
		texture.extent().height())
{}

BKSGE_INLINE
RenderBuffer::~RenderBuffer()
{
	::glDeleteRenderbuffers(1, &m_id);
}

BKSGE_INLINE void
RenderBuffer::Bind(void) const
{
	::glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

BKSGE_INLINE void
RenderBuffer::Unbind(void) const
{
	::glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

BKSGE_INLINE ::GLuint
RenderBuffer::name(void) const
{
	return m_id;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_BUFFER_INL_HPP
