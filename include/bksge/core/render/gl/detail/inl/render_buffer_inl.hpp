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

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
RenderBuffer::RenderBuffer(
	::GLenum format,
	bksge::uint32_t width,
	bksge::uint32_t height)
{
	::glGenRenderbuffers(1, &m_id);
	Bind();
	::glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

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
