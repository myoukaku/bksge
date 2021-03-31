/**
 *	@file	clear_state_inl.hpp
 *
 *	@brief	ClearState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_CLEAR_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_CLEAR_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/clear_state.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/clear_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLbitfield ToGlClearMask(ClearFlag flag)
{
	::GLbitfield mask = 0;
	if (Test(flag, ClearFlag::kColor))
	{
		mask |= GL_COLOR_BUFFER_BIT;
	}
	if (Test(flag, ClearFlag::kDepth))
	{
		mask |= GL_DEPTH_BUFFER_BIT;
	}
	if (Test(flag, ClearFlag::kStencil))
	{
		mask |= GL_STENCIL_BUFFER_BIT;
	}
	return mask;
}

}	// namespace detail

BKSGE_INLINE
ClearState::ClearState(bksge::ClearState const& state)
	: m_mask(detail::ToGlClearMask(state.flag()))
	, m_red  (state.color().r())
	, m_green(state.color().g())
	, m_blue (state.color().b())
	, m_alpha(state.color().a())
	, m_depth(state.depth())
	, m_stencil(state.stencil())
{}

BKSGE_INLINE void
ClearState::Apply(void)
{
	// カラーバッファをクリアするときは
	// glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE)を呼ぶ必要がある
	if (m_mask & GL_COLOR_BUFFER_BIT)
	{
		::glClearColor(m_red, m_green, m_blue, m_alpha);
		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

	// デプスバッファをクリアするときは
	// glDepthMask(GL_TRUE)を呼ぶ必要がある
	if (m_mask & GL_DEPTH_BUFFER_BIT)
	{
		::glClearDepth(m_depth);
		::glDepthMask(GL_TRUE);
	}

	// ステンシルバッファをクリアするときは
	// glStencilMask(0xFFFFFFFF)を呼ぶ必要がある
	if (m_mask & GL_STENCIL_BUFFER_BIT)
	{
		::glClearStencil(m_stencil);
		::glStencilMask(~0u);
	}

	::glDisable(GL_SCISSOR_TEST);
	::glClear(m_mask);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_CLEAR_STATE_INL_HPP
