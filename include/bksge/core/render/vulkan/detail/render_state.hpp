/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_STATE_HPP

#include <bksge/core/render/vulkan/detail/rasterizer_state.hpp>
#include <bksge/core/render/vulkan/detail/blend_state.hpp>
#include <bksge/core/render/vulkan/detail/depth_stencil_state.hpp>
#include <bksge/core/render/fwd/render_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class RenderState
{
public:
	explicit RenderState(bksge::RenderState const& state);

	vulkan::RasterizerState		const& rasterizer_state(void) const;
	vulkan::BlendState			const& blend_state(void) const;
	vulkan::DepthStencilState	const& depth_stencil_state(void) const;

private:
	vulkan::RasterizerState		m_rasterizer_state;
	vulkan::BlendState			m_blend_state;
	vulkan::DepthStencilState	m_depth_stencil_state;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/render_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_RENDER_STATE_HPP
