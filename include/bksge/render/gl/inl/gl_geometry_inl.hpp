/**
 *	@file	gl_geometry_inl.hpp
 *
 *	@brief	GlGeometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_GEOMETRY_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_GEOMETRY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_geometry.hpp>
#include <bksge/render/gl/gl_primitive.hpp>
#include <bksge/render/gl/gl_type_enum.hpp>
#include <bksge/render/geometry.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlGeometry::GlGeometry(Geometry const& geometry)
	: m_vertex_buffer(geometry.vertex_array_data(), geometry.vertex_array_bytes())
	, m_index_buffer(geometry.index_array_data(), geometry.index_array_bytes())
	, m_primitive(ToGlPrimitive(geometry.primitive()))
	, m_vertex_count(static_cast<GLsizei>(geometry.vertex_array_count()))
	, m_index_count(static_cast<GLsizei>(geometry.index_array_count()))
	, m_index_type(ToGlTypeEnum(geometry.index_array_type()))
{}

BKSGE_INLINE
GlGeometry::~GlGeometry()
{}

BKSGE_INLINE
void GlGeometry::Bind(void) const
{
	m_vertex_buffer.Bind();
	if (m_index_buffer.enable())
	{
		m_index_buffer.Bind();
	}
}

BKSGE_INLINE
void GlGeometry::Draw(void) const
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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_GEOMETRY_INL_HPP
