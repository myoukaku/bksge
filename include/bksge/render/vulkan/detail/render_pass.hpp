/**
 *	@file	render_pass.hpp
 *
 *	@brief	RenderPass クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct RenderPassCreateInfo : public ::VkRenderPassCreateInfo
{
	RenderPassCreateInfo(void)
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
};

class RenderPass
{
public:
	explicit RenderPass(
		std::shared_ptr<vk::Device> const& device,
		vk::RenderPassCreateInfo const& info)
		: m_render_pass(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreateRenderPass(*m_device, &info, nullptr, &m_render_pass);
	}

	~RenderPass()
	{
		vk::DestroyRenderPass(*m_device, m_render_pass, nullptr);
	}

	operator ::VkRenderPass() const
	{
		return m_render_pass;
	}

private:
	::VkRenderPass				m_render_pass;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_RENDER_PASS_HPP
