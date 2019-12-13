/**
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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
RenderPassBeginInfo::RenderPassBeginInfo(void)
{
	sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	pNext           = nullptr;
	renderPass      = VK_NULL_HANDLE;
	framebuffer     = VK_NULL_HANDLE;
	renderArea      = {{0,0},{0,0}};
	clearValueCount = 0;
	pClearValues    = nullptr;
}

BKSGE_INLINE
RenderPassCreateInfo::RenderPassCreateInfo(void)
{
	sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	pNext           = nullptr;
	flags           = 0;
	attachmentCount = 0;
	pAttachments    = nullptr;
	subpassCount    = 0;
	pSubpasses      = nullptr;
	dependencyCount = 0;
	pDependencies   = nullptr;
}

BKSGE_INLINE
RenderPass::RenderPass(
	std::shared_ptr<vk::Device> const& device,
	vk::RenderPassCreateInfo const& info)
	: m_render_pass(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreateRenderPass(*m_device, &info, nullptr, &m_render_pass);
}

BKSGE_INLINE
RenderPass::~RenderPass()
{
	vk::DestroyRenderPass(*m_device, m_render_pass, nullptr);
}

BKSGE_INLINE
RenderPass::operator ::VkRenderPass() const
{
	return m_render_pass;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_PASS_INL_HPP
