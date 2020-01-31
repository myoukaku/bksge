/**
 *	@file	image_object_fwd.hpp
 *
 *	@brief	ImageObject クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_OBJECT_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_OBJECT_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class ImageObject;
using ImageObjectUniquePtr = std::unique_ptr<ImageObject>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_OBJECT_FWD_HPP
