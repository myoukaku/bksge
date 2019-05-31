/**
 *	@file	pipeline_layout.hpp
 *
 *	@brief	PipelineLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct PipelineLayoutCreateInfo : public ::VkPipelineLayoutCreateInfo
{
	PipelineLayoutCreateInfo(void)
	{
		sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pNext                  = nullptr;
		flags                  = 0;
		setLayoutCount         = 0;
		pSetLayouts            = nullptr;
		pushConstantRangeCount = 0;
		pPushConstantRanges    = nullptr;
	}
};

class PipelineLayout
{
public:
	explicit PipelineLayout(
		std::shared_ptr<vk::Device> const& device,
		vk::PipelineLayoutCreateInfo const& info)
		: m_pipeline_layout(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreatePipelineLayout(*m_device, &info, nullptr, &m_pipeline_layout);
	}

	~PipelineLayout()
	{
		vk::DestroyPipelineLayout(*m_device, m_pipeline_layout, nullptr);
	}

	operator ::VkPipelineLayout() const
	{
		return m_pipeline_layout;
	}

private:
	::VkPipelineLayout			m_pipeline_layout;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP
