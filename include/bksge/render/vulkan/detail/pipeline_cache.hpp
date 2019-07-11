/**
 *	@file	pipeline_cache.hpp
 *
 *	@brief	PipelineCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP

#include <bksge/render/vulkan/detail/fwd/pipeline_cache_fwd.hpp>
#include <bksge/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct PipelineCacheCreateInfo : public ::VkPipelineCacheCreateInfo
{
	PipelineCacheCreateInfo(void);
};

class PipelineCache
{
public:
	explicit PipelineCache(
		std::shared_ptr<vk::Device> const& device,
		vk::PipelineCacheCreateInfo const& info);

	~PipelineCache();

	operator ::VkPipelineCache() const;

private:
	::VkPipelineCache			m_pipeline_cache;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/pipeline_cache_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP
