/**
 *	@file	swapchain_fwd.hpp
 *
 *	@brief	Swapchain クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SWAPCHAIN_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SWAPCHAIN_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Swapchain;
using SwapchainUniquePtr = bksge::unique_ptr<Swapchain>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SWAPCHAIN_FWD_HPP
