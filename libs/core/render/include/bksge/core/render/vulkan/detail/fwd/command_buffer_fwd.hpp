/**
 *	@file	command_buffer_fwd.hpp
 *
 *	@brief	CommandBuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMMAND_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMMAND_BUFFER_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CommandBuffer;
using CommandBufferUniquePtr = bksge::unique_ptr<CommandBuffer>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_COMMAND_BUFFER_FWD_HPP
