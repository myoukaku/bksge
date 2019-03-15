/**
 *	@file	gl_frame_buffer.hpp
 *
 *	@brief	GlFrameBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_GL_FRAME_BUFFER_HPP
#define BKSGE_RENDER_GL_GL_FRAME_BUFFER_HPP

#include <bksge/render/gl/fwd/gl_texture_fwd.hpp>
#include <bksge/render/gl/fwd/gl_render_buffer_fwd.hpp>
#include <bksge/render/gl/gl_api.hpp>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class GlFrameBuffer
{
public:
	GlFrameBuffer();

	~GlFrameBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	void CreateColorBuffers(void);

	void CreateDepthStencilBuffer(void);

	void CheckFramebufferStatus(void);

private:
	GLuint		m_id;
	std::vector<std::shared_ptr<GlTexture>>	m_color_buffers;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/inl/gl_frame_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_GL_FRAME_BUFFER_HPP
