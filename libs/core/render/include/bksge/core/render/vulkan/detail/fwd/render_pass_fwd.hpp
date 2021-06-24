/**
 *	@file	render_pass_fwd.hpp
 *
 *	@brief	RenderPass クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_RENDER_PASS_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_RENDER_PASS_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class RenderPass;
using RenderPassSharedPtr = bksge::shared_ptr<RenderPass>;
using RenderPassUniquePtr = bksge::unique_ptr<RenderPass>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_RENDER_PASS_FWD_HPP
