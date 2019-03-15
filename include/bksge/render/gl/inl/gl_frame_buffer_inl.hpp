/**
 *	@file	gl_frame_buffer_inl.hpp
 *
 *	@brief	GlFrameBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_FRAME_BUFFER_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_FRAME_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_frame_buffer.hpp>
#include <bksge/render/gl/gl_texture.hpp>
#include <bksge/render/texture_format.hpp>
#include <bksge/memory/make_unique.hpp>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GlFrameBuffer::GlFrameBuffer()
{
	glGenFramebuffersEXT(1, &m_id);

	Bind();

	CreateColorBuffers();

	CreateDepthStencilBuffer();

	CheckFramebufferStatus();
}

BKSGE_INLINE
GlFrameBuffer::~GlFrameBuffer()
{
	glDeleteFramebuffersEXT(1, &m_id);
}

BKSGE_INLINE
void GlFrameBuffer::Bind(void) const
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_id);
}

BKSGE_INLINE
void GlFrameBuffer::Unbind(void) const
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

BKSGE_INLINE
void GlFrameBuffer::CreateColorBuffers(void)
{
	int width  = 800;
	int height = 600;

	for (int i = 0; i < 1; i++)
	{
		auto gl_texture = bksge::make_unique<GlTexture>(TextureFormat::kRGBA_U8, width, height, nullptr);

		glFramebufferTexture2DEXT(
			GL_FRAMEBUFFER_EXT,
			GL_COLOR_ATTACHMENT0_EXT + i,
			GL_TEXTURE_2D,
			gl_texture->name(),
			0);

		m_color_buffers.push_back(std::move(gl_texture));
	}
}

BKSGE_INLINE
void GlFrameBuffer::CreateDepthStencilBuffer(void)
{
}

BKSGE_INLINE
void GlFrameBuffer::CheckFramebufferStatus(void)
{
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_FRAME_BUFFER_INL_HPP
