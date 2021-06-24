/**
 *	@file	semaphore_fwd.hpp
 *
 *	@brief	Semaphore クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SEMAPHORE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SEMAPHORE_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Semaphore;
using SemaphoreUniquePtr = bksge::unique_ptr<Semaphore>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SEMAPHORE_FWD_HPP
