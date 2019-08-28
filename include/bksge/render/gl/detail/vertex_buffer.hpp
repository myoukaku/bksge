/**
 *	@file	vertex_buffer.hpp
 *
 *	@brief	VertexBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_VERTEX_BUFFER_HPP
#define BKSGE_RENDER_GL_DETAIL_VERTEX_BUFFER_HPP

#include <bksge/render/gl/detail/gl_h.hpp>
#include <cstddef>

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
	VertexBuffer(void const* src, std::size_t size);

	~VertexBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	::GLuint m_id;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_VERTEX_BUFFER_HPP
