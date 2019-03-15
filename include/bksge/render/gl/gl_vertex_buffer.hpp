/**
 *	@file	gl_vertex_buffer.hpp
 *
 *	@brief	GlVertexBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_VERTEX_BUFFER_HPP
#define BKSGE_RENDER_GL_GL_VERTEX_BUFFER_HPP

#include <bksge/render/gl/gl_api.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

/**
 *	@brief	OpenGLでの頂点バッファ
 */
class GlVertexBuffer
{
public:
	GlVertexBuffer(void const* src, std::size_t size);

	~GlVertexBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	GLuint m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_vertex_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_VERTEX_BUFFER_HPP
