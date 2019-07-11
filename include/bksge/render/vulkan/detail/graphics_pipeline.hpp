/**
 *	@file	graphics_pipeline.hpp
 *
 *	@brief	GraphicsPipeline クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP

#include <bksge/render/vulkan/detail/fwd/graphics_pipeline_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/pipeline_cache_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct PipelineDynamicStateCreateInfo : public ::VkPipelineDynamicStateCreateInfo
{
	PipelineDynamicStateCreateInfo(void);
};

struct PipelineVertexInputStateCreateInfo : public ::VkPipelineVertexInputStateCreateInfo
{
	PipelineVertexInputStateCreateInfo(void);
};

struct PipelineInputAssemblyStateCreateInfo : public ::VkPipelineInputAssemblyStateCreateInfo
{
	PipelineInputAssemblyStateCreateInfo(void);
};

struct PipelineRasterizationStateCreateInfo : public ::VkPipelineRasterizationStateCreateInfo
{
	PipelineRasterizationStateCreateInfo(void);
};

struct PipelineColorBlendAttachmentState : public ::VkPipelineColorBlendAttachmentState
{
	PipelineColorBlendAttachmentState(void);
};

struct PipelineColorBlendStateCreateInfo : public ::VkPipelineColorBlendStateCreateInfo
{
	PipelineColorBlendStateCreateInfo(void);
};

struct PipelineViewportStateCreateInfo : public ::VkPipelineViewportStateCreateInfo
{
	PipelineViewportStateCreateInfo(void);
};

struct PipelineDepthStencilStateCreateInfo : public ::VkPipelineDepthStencilStateCreateInfo
{
	PipelineDepthStencilStateCreateInfo(void);
};

struct PipelineMultisampleStateCreateInfo : public ::VkPipelineMultisampleStateCreateInfo
{
	PipelineMultisampleStateCreateInfo(void);
};

struct GraphicsPipelineCreateInfo : public ::VkGraphicsPipelineCreateInfo
{
	GraphicsPipelineCreateInfo(void);
};

class GraphicsPipeline
{
public:
	explicit GraphicsPipeline(
		std::shared_ptr<vk::Device> const& device,
		vk::PipelineCache const& cache,
		vk::GraphicsPipelineCreateInfo const& info);

	~GraphicsPipeline();

	operator ::VkPipeline() const;

private:
	::VkPipeline				m_pipeline;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/graphics_pipeline_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP
