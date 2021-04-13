/**
 *	@file	render_state_inl.hpp
 *
 *	@brief	RenderState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/render_state.hpp>
#include <bksge/core/render/render_state.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
RenderState::RenderState(bksge::RenderState const& state)
	: m_rasterizer_state(state.rasterizer_state())
	, m_blend_state(state.blend_state())
	, m_depth_stencil_state(state.depth_state(), state.stencil_state())
{}

BKSGE_INLINE vulkan::RasterizerState const&
RenderState::rasterizer_state(void) const
{
	return m_rasterizer_state;
}

BKSGE_INLINE vulkan::BlendState const&
RenderState::blend_state(void) const
{
	return m_blend_state;
}

BKSGE_INLINE vulkan::DepthStencilState const&
RenderState::depth_stencil_state(void) const
{
	return m_depth_stencil_state;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_STATE_INL_HPP
