/**
 *	@file	image_view_fwd.hpp
 *
 *	@brief	ImageView クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_VIEW_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_VIEW_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class ImageView;
using ImageViewUniquePtr = std::unique_ptr<ImageView>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_IMAGE_VIEW_FWD_HPP
