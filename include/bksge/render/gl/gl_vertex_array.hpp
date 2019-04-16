/**
 *	@file	gl_vertex_array.hpp
 *
 *	@brief	GlVertexArray の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_VERTEX_ARRAY_HPP
#define BKSGE_RENDER_GL_GL_VERTEX_ARRAY_HPP

#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <bksge/render/gl/gl_vertex_buffer.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	Vertex Array Object (VAO)
 */
class GlVertexArray
{
public:
	GlVertexArray(Geometry const& geometry);

	~GlVertexArray();

	void Bind(void) const;

	void Unbind(void) const;

private:
	GLuint			m_id;
	GlVertexBuffer	m_vertex_buffer;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_vertex_array_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_VERTEX_ARRAY_HPP
