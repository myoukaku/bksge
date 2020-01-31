/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_GEOMETRY_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_GEOMETRY_HPP

#include <bksge/core/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/core/render/fwd/geometry_fwd.hpp>
#include <bksge/core/render/gl/detail/vertex_array.hpp>
#include <bksge/core/render/gl/detail/index_buffer.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Geometry を OpenGL で使えるように変換したクラス
 */
class Geometry
{
public:
	explicit Geometry(bksge::Geometry const& geometry);

	~Geometry();

	void Bind(void) const;
	void Unbind(void) const;

	void Draw(void) const;

private:
	VertexArray		m_vertex_array;
	IndexBuffer		m_index_buffer;
	::GLenum		m_primitive_topology;
	::GLsizei		m_vertex_count;
	::GLsizei		m_index_count;
	::GLenum		m_index_type;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_GEOMETRY_HPP
