/**
 *	@file	scissor_state_inl.hpp
 *
 *	@brief	ScissorState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SCISSOR_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SCISSOR_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/scissor_state.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/scissor_state.hpp>
#include <bksge/core/render/viewport.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
ScissorState::ScissorState(
	bksge::ScissorState const& scissor_state,
	bksge::Viewport const& viewport)
{
	auto const rect =
		scissor_state.enable() ?
		scissor_state.rect() :
		viewport.rect();
	m_rect.offset.x = static_cast<bksge::int32_t>(bksge::max(0.0f, rect.left()));
	m_rect.offset.y = static_cast<bksge::int32_t>(bksge::max(0.0f, rect.top()));
	m_rect.extent.width  = static_cast<bksge::uint32_t>(rect.width());
	m_rect.extent.height = static_cast<bksge::uint32_t>(rect.height());
}

BKSGE_INLINE ::VkRect2D const&
ScissorState::rect(void) const
{
	return m_rect;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_SCISSOR_STATE_INL_HPP
