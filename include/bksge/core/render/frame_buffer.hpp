/**
 *	@file	frame_buffer.hpp
 *
 *	@brief	FrameBuffer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FRAME_BUFFER_HPP
#define BKSGE_CORE_RENDER_FRAME_BUFFER_HPP

#include <bksge/core/render/fwd/frame_buffer_fwd.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
#include <bksge/core/render/render_texture.hpp>

namespace bksge
{

namespace render
{

class FrameBuffer : public Identifiable
{
public:
	FrameBuffer(RenderTexture const& color, RenderTexture const& depth_stencil);

	RenderTexture const&	color(void) const { return m_color; }
	RenderTexture const&	depth_stencil(void) const { return m_depth_stencil; }

private:
	RenderTexture	m_color;
	RenderTexture	m_depth_stencil;
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/frame_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_FRAME_BUFFER_HPP
