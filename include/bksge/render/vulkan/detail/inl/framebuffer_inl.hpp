/**
 *	@file	framebuffer_inl.hpp
 *
 *	@brief	Framebuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/framebuffer.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
FramebufferCreateInfo::FramebufferCreateInfo(void)
{
	sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	pNext           = nullptr;
	flags           = 0;
	renderPass      = VK_NULL_HANDLE;
	attachmentCount = 0;
	pAttachments    = nullptr;
	width           = 0;
	height          = 0;
	layers          = 0;
}

BKSGE_INLINE
Framebuffer::Framebuffer(
	std::shared_ptr<vk::Device> const& device,
	vk::FramebufferCreateInfo const& info)
	: m_framebuffer(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreateFramebuffer(*m_device, &info, nullptr, &m_framebuffer);
}

BKSGE_INLINE
Framebuffer::~Framebuffer()
{
	vk::DestroyFramebuffer(*m_device, m_framebuffer, nullptr);
}

BKSGE_INLINE
Framebuffer::operator ::VkFramebuffer() const
{
	return m_framebuffer;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
