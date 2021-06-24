/**
 *	@file	vertex_buffer_inl.hpp
 *
 *	@brief	VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_VERTEX_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_VERTEX_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/vertex_buffer.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
VertexBuffer::VertexBuffer(void const* src, bksge::size_t size)
	: m_id(0)
{
	::glGenBuffers(1, &m_id);
	Bind();
	::glBufferData(GL_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
}

BKSGE_INLINE
VertexBuffer::~VertexBuffer()
{
	::glDeleteBuffers(1, &m_id);
}

BKSGE_INLINE void
VertexBuffer::Bind(void) const
{
	::glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

BKSGE_INLINE void
VertexBuffer::Unbind(void) const
{
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_VERTEX_BUFFER_INL_HPP
