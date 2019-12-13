/**
 *	@file	pipeline_cache_inl.hpp
 *
 *	@brief	PipelineCache クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
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

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP
