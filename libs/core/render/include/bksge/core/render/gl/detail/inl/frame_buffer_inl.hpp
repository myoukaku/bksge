/**
 *	@file	frame_buffer_inl.hpp
 *
 *	@brief	FrameBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_FRAME_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_FRAME_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/frame_buffer.hpp>
#include <bksge/core/render/gl/detail/texture.hpp>
#include <bksge/core/render/gl/detail/render_buffer.hpp>
#include <bksge/core/render/gl/detail/resource_pool.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/core/render/frame_buffer.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
FrameBuffer::FrameBuffer()
{
	::glGenFramebuffers(1, &m_id);

	//Bind();

	//CheckFramebufferStatus();
}

BKSGE_INLINE
FrameBuffer::FrameBuffer(
	bksge::FrameBuffer const& frame_buffer,
	ResourcePool* resource_pool)
{
	::glGenFramebuffers(1, &m_id);

	{
		auto gl_color = resource_pool->GetGlTexture(
			frame_buffer.color());
		this->AttachColorBuffer(0, gl_color);
	}
	{
		auto gl_depth_stencil = resource_pool->GetGlRenderBuffer(
			frame_buffer.depth_stencil());
		this->AttachDepthStencilBuffer(gl_depth_stencil);
	}
}

BKSGE_INLINE
FrameBuffer::~FrameBuffer()
{
	::glDeleteFramebuffers(1, &m_id);
}

BKSGE_INLINE void
FrameBuffer::Bind(void) const
{
	::glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

BKSGE_INLINE void
FrameBuffer::Unbind(void) const
{
	::glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

BKSGE_INLINE void
FrameBuffer::AttachColorBuffer(std::size_t index, TextureShared const& texture)
{
	if (index >= m_color_buffers.size())
	{
		m_color_buffers.resize(index+1);
	}

	m_color_buffers[index] = texture;

	Bind();
	::glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		static_cast<::GLenum>(GL_COLOR_ATTACHMENT0 + index),
		GL_TEXTURE_2D,
		texture->name(),
		0);
}

BKSGE_INLINE void
FrameBuffer::AttachDepthStencilBuffer(gl::RenderBufferShared const& buffer)
{
	m_depth_stencil_buffer = buffer;
	Bind();
	::glFramebufferRenderbuffer(
		GL_FRAMEBUFFER,
		GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER,
		buffer->name());
}

BKSGE_INLINE gl::TextureShared const&
FrameBuffer::GetColorBuffer(std::size_t index) const
{
	return m_color_buffers[index];
}

//BKSGE_INLINE void
//FrameBuffer::CheckFramebufferStatus(void)
//{
//}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_FRAME_BUFFER_INL_HPP
