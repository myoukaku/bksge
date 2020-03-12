﻿/**
 *	@file	pipeline_layout_fwd.hpp
 *
 *	@brief	PipelineLayout クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_PIPELINE_LAYOUT_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_PIPELINE_LAYOUT_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class PipelineLayout;
using PipelineLayoutUniquePtr = std::unique_ptr<PipelineLayout>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_PIPELINE_LAYOUT_FWD_HPP
