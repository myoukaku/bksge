/**
 *	@file	pipeline_cache.hpp
 *
 *	@brief	PipelineCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

struct PipelineCacheCreateInfo : public ::VkPipelineCacheCreateInfo
{
	PipelineCacheCreateInfo(void)
	{
		sType           = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		pNext           = nullptr;
		flags           = 0;
		initialDataSize = 0;
		pInitialData    = nullptr;
	}
};

class PipelineCache
{
public:
	explicit PipelineCache(
		std::shared_ptr<vk::Device> const& device,
		vk::PipelineCacheCreateInfo const& info)
		: m_pipeline_cache(VK_NULL_HANDLE)
		, m_device(device)
	{
		vk::CreatePipelineCache(*m_device, &info, nullptr, &m_pipeline_cache);
	}

	~PipelineCache()
	{
		vk::DestroyPipelineCache(*m_device, m_pipeline_cache, nullptr);
	}

	operator ::VkPipelineCache() const
	{
		return m_pipeline_cache;
	}

private:
	::VkPipelineCache			m_pipeline_cache;
	std::shared_ptr<vk::Device>	m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP
