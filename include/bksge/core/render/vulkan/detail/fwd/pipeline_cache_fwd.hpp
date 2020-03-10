/**
 *	@file	pipeline_cache_fwd.hpp
 *
 *	@brief	PipelineCache クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_PIPELINE_CACHE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_PIPELINE_CACHE_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class PipelineCache;
using PipelineCacheUniquePtr = bksge::unique_ptr<PipelineCache>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_PIPELINE_CACHE_FWD_HPP
