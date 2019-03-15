/**
 *	@file	gl_index_buffer.hpp
 *
 *	@brief	GlIndexBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_INDEX_BUFFER_HPP
#define BKSGE_RENDER_GL_GL_INDEX_BUFFER_HPP

#include <bksge/render/gl/gl_api.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

/**
 *	@brief	OpenGLでのインデックスバッファ
 */
class GlIndexBuffer
{
public:
	GlIndexBuffer(void const* src, std::size_t size);

	~GlIndexBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	GLuint m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_index_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_INDEX_BUFFER_HPP
