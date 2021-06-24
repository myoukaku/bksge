/**
 *	@file	queue_fwd.hpp
 *
 *	@brief	Queue クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_QUEUE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_QUEUE_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Queue;
using QueueUniquePtr = bksge::unique_ptr<Queue>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_QUEUE_FWD_HPP
