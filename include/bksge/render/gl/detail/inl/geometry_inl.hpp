/**
 *	@file	geometry_inl.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_GEOMETRY_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_GEOMETRY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/geometry.hpp>
#include <bksge/render/gl/detail/primitive.hpp>
#include <bksge/render/gl/detail/type_enum.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
Geometry::Geometry(bksge::Geometry const& geometry)
	: m_vertex_array(geometry)
	, m_index_buffer(geometry.index_array_data(), geometry.index_array_bytes())
	, m_primitive(gl::Primitive(geometry.primitive()))
	, m_vertex_count(static_cast<::GLsizei>(geometry.vertex_array_count()))
	, m_index_count(static_cast<::GLsizei>(geometry.index_array_count()))
	, m_index_type(gl::TypeEnum(geometry.index_array_type()))
{}

BKSGE_INLINE
Geometry::~Geometry()
{}

BKSGE_INLINE void
Geometry::Bind(void) const
{
	m_vertex_array.Bind();

	if (m_index_buffer.enable())
	{
		m_index_buffer.Bind();
	}
}

BKSGE_INLINE void
Geometry::Unbind(void) const
{
	m_vertex_array.Unbind();

	if (m_index_buffer.enable())
	{
		m_index_buffer.Unbind();
	}
}

BKSGE_INLINE void
Geometry::Draw(void) const
{
	if (m_index_buffer.enable())
	{
		::glDrawElements(m_primitive, m_index_count, m_index_type, 0);
	}
	else
	{
		::glDrawArrays(m_primitive, 0, m_vertex_count);
	}
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_GEOMETRY_INL_HPP
