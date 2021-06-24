/**
 *	@file	fence_fwd.hpp
 *
 *	@brief	Fence クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FENCE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FENCE_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Fence;
using FenceUniquePtr = bksge::unique_ptr<Fence>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FENCE_FWD_HPP
