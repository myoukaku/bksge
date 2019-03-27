/**
 *	@file	gl_vertex_buffer_inl.hpp
 *
 *	@brief	GlVertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_VERTEX_BUFFER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_VERTEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_vertex_buffer.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlVertexBuffer::GlVertexBuffer(void const* src, std::size_t size)
	: m_id(0)
{
	::glGenBuffers(1, &m_id);
	Bind();
	::glBufferData(GL_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
}

BKSGE_INLINE
GlVertexBuffer::~GlVertexBuffer()
{
	::glDeleteBuffers(1, &m_id);
}

BKSGE_INLINE
void GlVertexBuffer::Bind(void) const
{
	::glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

BKSGE_INLINE
void GlVertexBuffer::Unbind(void) const
{
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_VERTEX_BUFFER_INL_HPP
