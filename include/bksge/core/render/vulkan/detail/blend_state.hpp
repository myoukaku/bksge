/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_STATE_HPP

#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/blend_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class BlendState
{
public:
	explicit BlendState(bksge::BlendState const& blend_state);

	::VkPipelineColorBlendStateCreateInfo const* GetAddressOf(void) const;

private:
	::VkPipelineColorBlendAttachmentState	 m_attachment_state;
	vk::PipelineColorBlendStateCreateInfo	 m_blend_state;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_STATE_HPP
