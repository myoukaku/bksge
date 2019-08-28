/**
 *	@file	frame_buffer_inl.hpp
 *
 *	@brief	FrameBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_FRAME_BUFFER_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_FRAME_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/frame_buffer.hpp>
#include <bksge/render/gl/detail/texture.hpp>
#include <bksge/render/texture_format.hpp>
#include <bksge/memory/make_unique.hpp>
#include <utility>

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

	Bind();

	CreateColorBuffers();

	CreateDepthStencilBuffer();

	CheckFramebufferStatus();
}

BKSGE_INLINE
FrameBuffer::~FrameBuffer()
{
	::glDeleteFramebuffers(1, &m_id);
}

BKSGE_INLINE void
FrameBuffer::Bind(void) const
{
	::glBindFramebuffer(GL_FRAMEBUFFER_EXT, m_id);
}

BKSGE_INLINE void
FrameBuffer::Unbind(void) const
{
	::glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
}

BKSGE_INLINE void
FrameBuffer::CreateColorBuffers(void)
{
	int width  = 800;
	int height = 600;

	for (int i = 0; i < 1; i++)
	{
		auto gl_texture =
			bksge::make_unique<Texture>(
				bksge::TextureFormat::kRGBA_U8, width, height, nullptr);

		::glFramebufferTexture2D(
			GL_FRAMEBUFFER_EXT,
			GL_COLOR_ATTACHMENT0_EXT + i,
			GL_TEXTURE_2D,
			gl_texture->name(),
			0);

		m_color_buffers.push_back(std::move(gl_texture));
	}
}

BKSGE_INLINE void
FrameBuffer::CreateDepthStencilBuffer(void)
{
}

BKSGE_INLINE void
FrameBuffer::CheckFramebufferStatus(void)
{
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_FRAME_BUFFER_INL_HPP
