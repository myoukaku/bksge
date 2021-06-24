/**
 *	@file	frame_buffer_inl.hpp
 *
 *	@brief	FrameBuffer の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_FRAME_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_INL_FRAME_BUFFER_INL_HPP

#include <bksge/core/render/frame_buffer.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
FrameBuffer::FrameBuffer(
	RenderTexture const& color,
	RenderTexture const& depth_stencil)
	: m_color(color)
	, m_depth_stencil(depth_stencil)
{
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_FRAME_BUFFER_INL_HPP
