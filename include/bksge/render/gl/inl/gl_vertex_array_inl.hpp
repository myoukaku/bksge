/**
 *	@file	gl_vertex_array_inl.hpp
 *
 *	@brief	GlVertexArray クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_VERTEX_ARRAY_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_VERTEX_ARRAY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_vertex_array.hpp>
#include <bksge/render/gl/gl_type_enum.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlVertexArray::GlVertexArray(Geometry const& geometry)
	: m_id(0)
	, m_vertex_buffer(geometry.vertex_array_data(), geometry.vertex_array_bytes())
{
	::glGenVertexArrays(1, &m_id);
	Bind();
	m_vertex_buffer.Bind();

	auto const& layout = geometry.vertex_layout();
	auto const stride = static_cast<GLsizei>(layout.total_bytes());

	GLuint index = 0;
	for (auto& attribute : layout.vertex_attribute_array())
	{
		auto const size = static_cast<GLint>(attribute.element_num());
		auto const offset = reinterpret_cast<const void*>(attribute.offset());
		auto const type = ToGlTypeEnum(attribute.type());
		::glEnableVertexAttribArray(index);
		::glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
		++index;
	}
}

BKSGE_INLINE
GlVertexArray::~GlVertexArray()
{
	::glDeleteVertexArrays(1, &m_id);
}

BKSGE_INLINE
void GlVertexArray::Bind(void) const
{
	::glBindVertexArray(m_id);
}

BKSGE_INLINE
void GlVertexArray::Unbind(void) const
{
	::glBindVertexArray(0);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_VERTEX_ARRAY_INL_HPP
