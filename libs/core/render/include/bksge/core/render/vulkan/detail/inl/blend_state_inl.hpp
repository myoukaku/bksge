/**
 *	@file	blend_state_inl.hpp
 *
 *	@brief	BlendState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/blend_state.hpp>
#include <bksge/core/render/vulkan/detail/blend_factor.hpp>
#include <bksge/core/render/vulkan/detail/blend_operation.hpp>
#include <bksge/core/render/vulkan/detail/bool.hpp>
#include <bksge/core/render/vulkan/detail/color_write_flag.hpp>
#include <bksge/core/render/vulkan/detail/logic_operation.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/blend_state.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
BlendState::BlendState(bksge::BlendState const& blend_state)
{
	m_attachment_state.blendEnable         = vulkan::Bool(blend_state.enable());
	m_attachment_state.srcColorBlendFactor = vulkan::BlendFactor(blend_state.color_src_factor());
	m_attachment_state.dstColorBlendFactor = vulkan::BlendFactor(blend_state.color_dst_factor());
	m_attachment_state.colorBlendOp        = vulkan::BlendOperation(blend_state.color_operation());
	m_attachment_state.srcAlphaBlendFactor = vulkan::BlendFactor(blend_state.alpha_src_factor());
	m_attachment_state.dstAlphaBlendFactor = vulkan::BlendFactor(blend_state.alpha_dst_factor());
	m_attachment_state.alphaBlendOp        = vulkan::BlendOperation(blend_state.alpha_operation());
	m_attachment_state.colorWriteMask      = vulkan::ColorWriteFlag(blend_state.color_write_mask());

	m_blend_state.SetAttachments(m_attachment_state);
	m_blend_state.logicOpEnable = vulkan::Bool(blend_state.logic_op_enable());
	m_blend_state.logicOp       = vulkan::LogicOperation(blend_state.logic_operation());
	m_blend_state.SetBlendConstants(1.0f, 1.0f, 1.0f, 1.0f);
}

BKSGE_INLINE ::VkPipelineColorBlendStateCreateInfo const*
BlendState::GetAddressOf(void) const
{
	return &m_blend_state;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_STATE_INL_HPP
