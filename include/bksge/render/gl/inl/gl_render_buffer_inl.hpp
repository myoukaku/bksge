/**
 *	@file	gl_render_buffer_inl.hpp
 *
 *	@brief	GlRenderBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_RENDER_BUFFER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_RENDER_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_render_buffer.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlRenderBuffer::GlRenderBuffer()
{
	glGenRenderbuffersEXT(1, &m_id);
}

BKSGE_INLINE
GlRenderBuffer::~GlRenderBuffer()
{
	glDeleteRenderbuffersEXT(1, &m_id);
}

BKSGE_INLINE
void GlRenderBuffer::Bind(void) const
{
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_id);
}

BKSGE_INLINE
void GlRenderBuffer::Unbind(void) const
{
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_RENDER_BUFFER_INL_HPP
