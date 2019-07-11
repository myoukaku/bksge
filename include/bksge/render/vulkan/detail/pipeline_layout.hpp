/**
 *	@file	pipeline_layout.hpp
 *
 *	@brief	PipelineLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP

#include <bksge/render/vulkan/detail/fwd/pipeline_layout_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct PipelineLayoutCreateInfo : public ::VkPipelineLayoutCreateInfo
{
	PipelineLayoutCreateInfo(void);
};

class PipelineLayout
{
public:
	explicit PipelineLayout(
		std::shared_ptr<vk::Device> const& device,
		vk::PipelineLayoutCreateInfo const& info);

	~PipelineLayout();

	operator ::VkPipelineLayout() const;

private:
	::VkPipelineLayout			m_pipeline_layout;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/pipeline_layout_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_LAYOUT_HPP
