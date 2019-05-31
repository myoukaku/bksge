/**
 *	@file	framebuffer.hpp
 *
 *	@brief	Framebuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct FramebufferCreateInfo : public ::VkFramebufferCreateInfo
{
	FramebufferCreateInfo(void)
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
};

class Framebuffer
{
public:
	explicit Framebuffer(
		std::shared_ptr<vk::Device> const& device,
		vk::FramebufferCreateInfo const& info)
		: m_framebuffer(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreateFramebuffer(*m_device, &info, nullptr, &m_framebuffer);
	}

	~Framebuffer()
	{
		vk::DestroyFramebuffer(*m_device, m_framebuffer, nullptr);
	}

	operator ::VkFramebuffer() const
	{
		return m_framebuffer;
	}

private:
	::VkFramebuffer				m_framebuffer;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_FRAMEBUFFER_HPP
