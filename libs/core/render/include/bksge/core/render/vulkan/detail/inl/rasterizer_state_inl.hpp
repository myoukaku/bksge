/**
 *	@file	rasterizer_state_inl.hpp
 *
 *	@brief	RasterizerState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RASTERIZER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RASTERIZER_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/rasterizer_state.hpp>
#include <bksge/core/render/vulkan/detail/fill_mode.hpp>
#include <bksge/core/render/vulkan/detail/front_face.hpp>
#include <bksge/core/render/vulkan/detail/cull_mode.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
RasterizerState::RasterizerState(bksge::RasterizerState const& state)
{
	auto& rs = m_rasterization_state;
	rs.polygonMode             = FillMode(state.fill_mode());
	rs.cullMode                = CullMode(state.cull_mode());
	rs.frontFace               = FrontFace(state.front_face());
	rs.depthClampEnable        = VK_FALSE;
	rs.rasterizerDiscardEnable = VK_FALSE;
	rs.depthBiasEnable         = VK_FALSE;
	rs.depthBiasConstantFactor = 0;
	rs.depthBiasClamp          = 0;
	rs.depthBiasSlopeFactor    = 0;
	rs.lineWidth               = 1.0f;
}

BKSGE_INLINE ::VkPipelineRasterizationStateCreateInfo const*
RasterizerState::GetAddressOf(void) const
{
	return &m_rasterization_state;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RASTERIZER_STATE_INL_HPP
