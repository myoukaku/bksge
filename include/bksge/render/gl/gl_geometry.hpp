/**
 *	@file	gl_geometry.hpp
 *
 *	@brief	GlGeometry の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_GEOMETRY_HPP
#define BKSGE_RENDER_GL_GL_GEOMETRY_HPP

#include <bksge/render/gl/fwd/gl_geometry_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/gl/gl_vertex_buffer.hpp>
#include <bksge/render/gl/gl_index_buffer.hpp>
#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	GeometryをOpenGLで使えるように変換したクラス
 */
class GlGeometry
{
public:
	explicit GlGeometry(Geometry const& geometry);

	~GlGeometry();

	void Bind(void) const;

	void Draw(void) const;

private:
	GlVertexBuffer	m_vertex_buffer;
	GlIndexBuffer	m_index_buffer;
	GLenum			m_primitive;
	GLsizei			m_index_count;
	GLenum			m_index_type;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_GEOMETRY_HPP
