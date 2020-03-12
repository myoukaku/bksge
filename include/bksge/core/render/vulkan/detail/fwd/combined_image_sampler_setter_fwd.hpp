/**
 *	@file	combined_image_sampler_setter_fwd.hpp
 *
 *	@brief	CombinedImageSamplerSetter クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMBINED_IMAGE_SAMPLER_SETTER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMBINED_IMAGE_SAMPLER_SETTER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CombinedImageSamplerSetter;
using CombinedImageSamplerSetterUniquePtr = std::unique_ptr<CombinedImageSamplerSetter>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMBINED_IMAGE_SAMPLER_SETTER_FWD_HPP
