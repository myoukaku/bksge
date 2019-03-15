/**
 *	@file	gl_render_buffer.hpp
 *
 *	@brief	GlRenderBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_RENDER_BUFFER_HPP
#define BKSGE_RENDER_GL_GL_RENDER_BUFFER_HPP

#include <bksge/render/gl/gl_api.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class GlRenderBuffer
{
public:
	GlRenderBuffer();

	~GlRenderBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	GLuint m_id;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_render_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_RENDER_BUFFER_HPP
