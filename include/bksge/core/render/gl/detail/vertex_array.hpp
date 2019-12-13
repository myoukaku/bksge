/**
 *	@file	vertex_array.hpp
 *
 *	@brief	VertexArray クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_VERTEX_ARRAY_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_VERTEX_ARRAY_HPP

#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/gl/detail/vertex_buffer.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Vertex Array Object (VAO)
 */
class VertexArray
{
public:
	explicit VertexArray(bksge::Geometry const& geometry);

	~VertexArray();

	void Bind(void) const;

	void Unbind(void) const;

private:
	::GLuint		m_id;
	VertexBuffer	m_vertex_buffer;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/vertex_array_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_VERTEX_ARRAY_HPP
