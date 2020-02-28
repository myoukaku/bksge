﻿/**
 *	@file	sampler_fwd.hpp
 *
 *	@brief	Sampler クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SAMPLER_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Sampler;
using SamplerSharedPtr = std::shared_ptr<Sampler>;
using SamplerSharedPtrMap = std::map<bksge::size_t, SamplerSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SAMPLER_FWD_HPP
