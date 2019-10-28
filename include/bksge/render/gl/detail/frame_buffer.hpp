﻿/**
 *	@file	frame_buffer.hpp
 *
 *	@brief	FrameBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_FRAME_BUFFER_HPP
#define BKSGE_RENDER_GL_DETAIL_FRAME_BUFFER_HPP

#include <bksge/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/render/gl/detail/fwd/render_buffer_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief
 */
class FrameBuffer
{
public:
	FrameBuffer();

	~FrameBuffer();

	void Bind(void) const;

	void Unbind(void) const;

private:
	void CreateColorBuffers(void);

	void CreateDepthStencilBuffer(void);

	void CheckFramebufferStatus(void);

private:
	::GLuint					m_id;
	std::vector<TextureShared>	m_color_buffers;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/frame_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_FRAME_BUFFER_HPP