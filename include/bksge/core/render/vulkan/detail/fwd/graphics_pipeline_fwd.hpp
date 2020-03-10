/**
 *	@file	graphics_pipeline_fwd.hpp
 *
 *	@brief	GraphicsPipeline クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_GRAPHICS_PIPELINE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_GRAPHICS_PIPELINE_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <map>

namespace bksge
{

namespace render
{

namespace vulkan
{

class GraphicsPipeline;
using GraphicsPipelineSharedPtr = bksge::shared_ptr<GraphicsPipeline>;
using GraphicsPipelineSharedPtrMap = std::map<bksge::size_t, GraphicsPipelineSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_GRAPHICS_PIPELINE_FWD_HPP
