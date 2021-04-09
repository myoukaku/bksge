/**
 *	@file	frame_buffer.hpp
 *
 *	@brief	FrameBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FRAME_BUFFER_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FRAME_BUFFER_HPP

#include <bksge/core/render/gl/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/gl/detail/fwd/render_buffer_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/fnd/vector.hpp>

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

	void AttachColorBuffer(bksge::size_t index, gl::TextureShared const& texture);

	void AttachDepthStencilBuffer(gl::RenderBufferShared const& buffer);

	gl::TextureShared const& GetColorBuffer(bksge::size_t index) const;

private:
	//void CreateColorBuffers(void);

	//void CreateDepthStencilBuffer(void);

	//void CheckFramebufferStatus(void);

private:
	// noncopyable
	FrameBuffer(FrameBuffer const&) = delete;
	FrameBuffer& operator=(FrameBuffer const&) = delete;

private:
	::GLuint							m_id;
	bksge::vector<gl::TextureShared>	m_color_buffers;
	gl::RenderBufferShared				m_depth_stencil_buffer;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/frame_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FRAME_BUFFER_HPP
