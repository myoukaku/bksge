/**
 *	@file	frame_buffer_fwd.hpp
 *
 *	@brief	FrameBuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FRAME_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FRAME_BUFFER_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/map/map.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class FrameBuffer;
using FrameBufferSharedPtr = bksge::shared_ptr<FrameBuffer>;
using FrameBufferSharedPtrMap = bksge::map<Identifier, FrameBufferSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FRAME_BUFFER_FWD_HPP
