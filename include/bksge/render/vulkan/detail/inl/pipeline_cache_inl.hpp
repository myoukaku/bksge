/**
 *	@file	pipeline_cache_inl.hpp
 *
 *	@brief	PipelineCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/render/vulkan/detail/pipeline_cache.hpp>
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
PipelineCacheCreateInfo::PipelineCacheCreateInfo(void)
{
	sType           = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
	pNext           = nullptr;
	flags           = 0;
	initialDataSize = 0;
	pInitialData    = nullptr;
}

BKSGE_INLINE
PipelineCache::PipelineCache(
	std::shared_ptr<vk::Device> const& device,
	vk::PipelineCacheCreateInfo const& info)
	: m_pipeline_cache(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreatePipelineCache(*m_device, &info, nullptr, &m_pipeline_cache);
}

BKSGE_INLINE
PipelineCache::~PipelineCache()
{
	vk::DestroyPipelineCache(*m_device, m_pipeline_cache, nullptr);
}

BKSGE_INLINE
PipelineCache::operator ::VkPipelineCache() const
{
	return m_pipeline_cache;
}

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP
