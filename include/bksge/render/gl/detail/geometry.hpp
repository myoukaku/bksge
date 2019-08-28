/**
 *	@file	geometry.hpp
 *
 *	@brief	Geometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_GEOMETRY_HPP
#define BKSGE_RENDER_GL_DETAIL_GEOMETRY_HPP

#include <bksge/render/gl/detail/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/gl/detail/vertex_array.hpp>
#include <bksge/render/gl/detail/index_buffer.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

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
	::GLenum		m_primitive;
	::GLsizei		m_vertex_count;
	::GLsizei		m_index_count;
	::GLenum		m_index_type;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/geometry_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_GEOMETRY_HPP
