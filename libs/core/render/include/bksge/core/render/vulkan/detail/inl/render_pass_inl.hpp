﻿/**
 *	@file	render_pass_inl.hpp
 *
 *	@brief	RenderPass クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_PASS_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_PASS_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
RenderPass::RenderPass(
	vulkan::DeviceSharedPtr const& device,
	::VkSampleCountFlagBits num_samples,
	vulkan::Image const* color,
	vulkan::Image const* depth_stencil)
	: m_render_pass(VK_NULL_HANDLE)
	, m_device(device)
	, m_samples(num_samples)
{
	bksge::vector<::VkAttachmentDescription> attachments;

	{
		::VkAttachmentDescription att;
		att.format         = color->format();
		att.samples        = num_samples;
		att.loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		att.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
		att.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		att.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
		att.finalLayout    = color->layout();
		att.flags          = 0;
		attachments.push_back(att);
	}

	if (depth_stencil)
	{
		::VkAttachmentDescription att;
		att.format         = depth_stencil->format();
		att.samples        = num_samples;
		att.loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		att.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
		att.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
		att.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
		att.finalLayout    = depth_stencil->layout();
		att.flags          = 0;
		attachments.push_back(att);
	}

	::VkAttachmentReference color_reference {};
	color_reference.attachment = 0;
	color_reference.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	::VkAttachmentReference depth_reference {};
	depth_reference.attachment = 1;
	depth_reference.layout     = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	vk::SubpassDescription subpass;
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.SetInputAttachments(nullptr);
	subpass.SetColorAttachments(color_reference);
	subpass.SetResolveAttachments(nullptr);
	subpass.SetDepthStencilAttachment(depth_stencil ? &depth_reference : nullptr);
	subpass.SetPreserveAttachments(nullptr);

	// Subpass dependency to wait for wsi image acquired semaphore before starting layout transition
	vk::SubpassDependency subpass_dependency;
	subpass_dependency.srcSubpass      = VK_SUBPASS_EXTERNAL;
	subpass_dependency.dstSubpass      = 0;
	subpass_dependency.srcStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpass_dependency.dstStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subpass_dependency.srcAccessMask   = 0;
	subpass_dependency.dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subpass_dependency.dependencyFlags = 0;

	vk::RenderPassCreateInfo rp_info;
	rp_info.SetAttachments(attachments);
	rp_info.SetSubpasses(subpass);
	rp_info.SetDependencies(subpass_dependency);

	m_render_pass = m_device->CreateRenderPass(rp_info);
}

BKSGE_INLINE
RenderPass::~RenderPass()
{
	m_device->DestroyRenderPass(m_render_pass);
}

BKSGE_INLINE ::VkSampleCountFlagBits
RenderPass::samples(void) const
{
	return m_samples;
}

BKSGE_INLINE
RenderPass::operator ::VkRenderPass() const
{
	return m_render_pass;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_PASS_INL_HPP
