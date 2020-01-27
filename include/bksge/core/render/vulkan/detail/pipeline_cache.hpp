/**
 *	@file	pipeline_cache.hpp
 *
 *	@brief	PipelineCache クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP

#include <bksge/core/render/vulkan/detail/fwd/pipeline_cache_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class PipelineCache
{
public:
	explicit PipelineCache(
		vulkan::DeviceSharedPtr const& device);

	~PipelineCache();

	operator ::VkPipelineCache() const;

private:
	vulkan::DeviceSharedPtr	m_device;
	::VkPipelineCache		m_pipeline_cache;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/pipeline_cache_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_CACHE_HPP
