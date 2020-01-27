/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_DEPTH_STENCIL_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_DEPTH_STENCIL_STATE_HPP

#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/depth_state_fwd.hpp>
#include <bksge/core/render/fwd/stencil_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DepthStencilState
{
public:
	explicit DepthStencilState(
		bksge::DepthState const& depth_state,
		bksge::StencilState const& stencil_state);

	::VkPipelineDepthStencilStateCreateInfo const* GetAddressOf(void) const;

private:
	vk::PipelineDepthStencilStateCreateInfo m_depth_stencil_state;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/depth_stencil_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_DEPTH_STENCIL_STATE_HPP
