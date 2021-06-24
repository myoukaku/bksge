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

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
PipelineCache::PipelineCache(
	vulkan::DeviceSharedPtr const& device)
	: m_pipeline_cache(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::PipelineCacheCreateInfo info;
	m_pipeline_cache = m_device->CreatePipelineCache(info);
}

BKSGE_INLINE
PipelineCache::~PipelineCache()
{
	m_device->DestroyPipelineCache(m_pipeline_cache);
}

BKSGE_INLINE
PipelineCache::operator ::VkPipelineCache() const
{
	return m_pipeline_cache;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_CACHE_INL_HPP
