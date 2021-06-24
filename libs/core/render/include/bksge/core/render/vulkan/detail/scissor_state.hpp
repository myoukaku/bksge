/**
 *	@file	scissor_state.hpp
 *
 *	@brief	ScissorState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SCISSOR_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SCISSOR_STATE_HPP

#include <bksge/core/render/fwd/scissor_state_fwd.hpp>
#include <bksge/core/render/fwd/viewport_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class ScissorState
{
public:
	explicit ScissorState(
		bksge::ScissorState const& scissor_state,
		bksge::Viewport const& viewport);

	::VkRect2D const& rect(void) const;

private:
	::VkRect2D m_rect;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/scissor_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SCISSOR_STATE_HPP
