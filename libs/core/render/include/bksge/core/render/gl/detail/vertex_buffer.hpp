/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_VERTEX_BUFFER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_VERTEX_BUFFER_HPP

#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	OpenGL での頂点バッファ
 */
class VertexBuffer
{
public:
	explicit VertexBuffer(void const* src, bksge::size_t size);

	~VertexBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	// noncopyable
	VertexBuffer(VertexBuffer const&) = delete;
	VertexBuffer& operator=(VertexBuffer const&) = delete;

private:
	::GLuint m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_VERTEX_BUFFER_HPP
