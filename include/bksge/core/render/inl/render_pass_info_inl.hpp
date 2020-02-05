/**
 *	@file	render_pass_info_inl.hpp
 *
 *	@brief	RenderPassInfo の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_RENDER_PASS_INFO_INL_HPP
#define BKSGE_CORE_RENDER_INL_RENDER_PASS_INFO_INL_HPP

#include <bksge/core/render/render_pass_info.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/core/render/scissor_state.hpp>
#include <bksge/core/render/viewport.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
RenderPassInfo::RenderPassInfo(void)
	: m_clear_state()
	, m_scissor_state()
	, m_viewport()
{
}

BKSGE_INLINE ClearState const&
RenderPassInfo::clear_state(void) const
{
	return m_clear_state;
}

BKSGE_INLINE ScissorState const&
RenderPassInfo::scissor_state(void) const
{
	return m_scissor_state;
}

BKSGE_INLINE Viewport const&
RenderPassInfo::viewport(void) const
{
	return m_viewport;
}

BKSGE_INLINE ClearState&
RenderPassInfo::clear_state(void)
{
	return m_clear_state;
}

BKSGE_INLINE ScissorState&
RenderPassInfo::scissor_state(void)
{
	return m_scissor_state;
}

BKSGE_INLINE Viewport&
RenderPassInfo::viewport(void)
{
	return m_viewport;
}

BKSGE_INLINE bool
operator==(RenderPassInfo const& lhs, RenderPassInfo const& rhs)
{
	return
		lhs.clear_state()   == rhs.clear_state()   &&
		lhs.scissor_state() == rhs.scissor_state() &&
		lhs.viewport()      == rhs.viewport();
}

BKSGE_INLINE bool
operator!=(RenderPassInfo const& lhs, RenderPassInfo const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_RENDER_PASS_INFO_INL_HPP
