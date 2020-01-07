/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_RASTERIZER_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_RASTERIZER_STATE_HPP

#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/fwd/rasterizer_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class RasterizerState
{
public:
	explicit RasterizerState(bksge::RasterizerState const& state);

	::VkPipelineRasterizationStateCreateInfo const* GetAddressOf(void) const;

private:
	vk::PipelineRasterizationStateCreateInfo m_rasterization_state;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/rasterizer_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_RASTERIZER_STATE_HPP
