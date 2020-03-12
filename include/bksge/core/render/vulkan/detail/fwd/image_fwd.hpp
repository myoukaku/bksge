﻿/**
 *	@file	image_fwd.hpp
 *
 *	@brief	Image クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Image;
using ImageUniquePtr = std::unique_ptr<Image>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_FWD_HPP
