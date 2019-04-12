/**
 *	@file	gl_index_buffer_inl.hpp
 *
 *	@brief	GlIndexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_INDEX_BUFFER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_INDEX_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_index_buffer.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlIndexBuffer::GlIndexBuffer(void const* src, std::size_t size)
	: m_id(0)
	, m_enable(false)
{
	if (src != nullptr && size != 0u)
	{
		m_enable = true;
		::glGenBuffers(1, &m_id);
		Bind();
		::glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
	}
}

BKSGE_INLINE
GlIndexBuffer::~GlIndexBuffer()
{
	if (m_enable)
	{
		::glDeleteBuffers(1, &m_id);
		m_enable = false;
	}
}

BKSGE_INLINE
void GlIndexBuffer::Bind(void) const
{
	if (m_enable)
	{
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}
}

BKSGE_INLINE
void GlIndexBuffer::Unbind(void) const
{
	if (m_enable)
	{
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

BKSGE_INLINE bool
GlIndexBuffer::enable(void) const
{
	return m_enable;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_INDEX_BUFFER_INL_HPP
