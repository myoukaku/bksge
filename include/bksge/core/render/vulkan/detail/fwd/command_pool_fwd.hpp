/**
 *	@file	command_pool_fwd.hpp
 *
 *	@brief	CommandPool クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMMAND_POOL_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMMAND_POOL_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CommandPool;
using CommandPoolSharedPtr = bksge::shared_ptr<CommandPool>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMMAND_POOL_FWD_HPP
