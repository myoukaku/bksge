/**
 *	@file	uniform_buffer_inl.hpp
 *
 *	@brief	UniformBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_UNIFORM_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_UNIFORM_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/uniform_buffer.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
UniformBuffer::UniformBuffer(void const* src, ::GLsizeiptr size, ::GLint binding)
	: m_id(0)
	, m_binding(binding)
{
	::glGenBuffers(1, &m_id);
	Bind();
	::glBufferData(GL_UNIFORM_BUFFER, size, src, GL_DYNAMIC_DRAW);
	Unbind();
}

BKSGE_INLINE
UniformBuffer::~UniformBuffer()
{
	::glDeleteBuffers(1, &m_id);
}

BKSGE_INLINE void
UniformBuffer::Bind(void) const
{
	::glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	::glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, m_id);
}

BKSGE_INLINE void
UniformBuffer::Unbind(void) const
{
	::glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_UNIFORM_BUFFER_INL_HPP
