/**
 *	@file	framebuffer_inl.hpp
 *
 *	@brief	Framebuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/framebuffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Framebuffer::Framebuffer(
	vulkan::DeviceSharedPtr const& device,
	::VkRenderPass const& render_pass,
	bksge::vector<::VkImageView> const& attachments,
	::VkExtent2D const& extent)
	: m_device(device)
	, m_framebuffer(VK_NULL_HANDLE)
	, m_extent(extent)
{
	vk::FramebufferCreateInfo info;
	info.renderPass      = render_pass;
	info.SetAttachments(attachments);
	info.SetExtent(extent);
	info.layers          = 1;

	vk::CreateFramebuffer(*m_device, &info, nullptr, &m_framebuffer);
}

BKSGE_INLINE
Framebuffer::~Framebuffer()
{
	vk::DestroyFramebuffer(*m_device, m_framebuffer, nullptr);
}

BKSGE_INLINE ::VkExtent2D const&
Framebuffer::extent(void) const
{
	return m_extent;
}

BKSGE_INLINE
Framebuffer::operator ::VkFramebuffer() const
{
	return m_framebuffer;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
