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
RenderBuffer::RenderBuffer()
{
	::glGenRenderbuffersEXT(1, &m_id);
}

BKSGE_INLINE
RenderBuffer::~RenderBuffer()
{
	::glDeleteRenderbuffersEXT(1, &m_id);
}

BKSGE_INLINE void
RenderBuffer::Bind(void) const
{
	::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_id);
}

BKSGE_INLINE void
RenderBuffer::Unbind(void) const
{
	::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_BUFFER_INL_HPP
