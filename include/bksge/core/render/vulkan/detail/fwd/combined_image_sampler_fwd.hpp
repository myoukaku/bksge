/**
 *	@file	combined_image_sampler_fwd.hpp
 *
 *	@brief	CombinedImageSampler クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMBINED_IMAGE_SAMPLER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMBINED_IMAGE_SAMPLER_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <map>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CombinedImageSampler;
using CombinedImageSamplerSharedPtr = bksge::shared_ptr<CombinedImageSampler>;
using CombinedImageSamplerSharedPtrMap = std::map<bksge::size_t, CombinedImageSamplerSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMBINED_IMAGE_SAMPLER_FWD_HPP
