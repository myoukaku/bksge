/**
 *	@file	framebuffer_fwd.hpp
 *
 *	@brief	Framebuffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FRAMEBUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FRAMEBUFFER_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Framebuffer;
using FramebufferSharedPtr = bksge::shared_ptr<Framebuffer>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_FRAMEBUFFER_FWD_HPP
