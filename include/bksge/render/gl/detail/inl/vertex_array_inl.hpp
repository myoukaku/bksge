/**
 *	@file	vertex_array_inl.hpp
 *
 *	@brief	VertexArray クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_VERTEX_ARRAY_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_VERTEX_ARRAY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/vertex_array.hpp>
#include <bksge/render/gl/detail/type_enum.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
VertexArray::VertexArray(bksge::Geometry const& geometry)
	: m_id(0)
	, m_vertex_buffer(geometry.vertex_array_data(), geometry.vertex_array_bytes())
{
	::glGenVertexArrays(1, &m_id);
	Bind();
	m_vertex_buffer.Bind();

	auto const& layout = geometry.vertex_layout();
	auto const stride = static_cast<::GLsizei>(layout.total_bytes());

	::GLuint index = 0;
	for (auto& attribute : layout.vertex_attribute_array())
	{
		auto const size = static_cast<::GLint>(attribute.element_num());
		auto const offset = reinterpret_cast<const void*>(attribute.offset());
		auto const type = gl::TypeEnum(attribute.type());
		::glEnableVertexAttribArray(index);
		::glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
		++index;
	}
}

BKSGE_INLINE
VertexArray::~VertexArray()
{
	::glDeleteVertexArrays(1, &m_id);
}

BKSGE_INLINE void
VertexArray::Bind(void) const
{
	::glBindVertexArray(m_id);
}

BKSGE_INLINE void
VertexArray::Unbind(void) const
{
	::glBindVertexArray(0);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_VERTEX_ARRAY_INL_HPP
