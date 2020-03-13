﻿/**
 *	@file	sampler_fwd.hpp
 *
 *	@brief	Sampler クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SAMPLER_FWD_HPP

#include <cstddef>
#include <memory>
#include <map>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Sampler;
using SamplerSharedPtr = std::shared_ptr<Sampler>;
using SamplerSharedPtrMap = std::map<std::size_t, SamplerSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SAMPLER_FWD_HPP
