/**
 *	@file	depth_state_inl.hpp
 *
 *	@brief	DepthState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_DEPTH_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_DEPTH_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/depth_state.hpp>
#include <bksge/core/render/gl/detail/bool.hpp>
#include <bksge/core/render/gl/detail/comparison_function.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/depth_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
DepthState::DepthState(bksge::DepthState const& state)
	: m_enable(state.enable())
	, m_write(gl::Bool(state.write()))
	, m_func(gl::ComparisonFunction(state.func()))
{}

BKSGE_INLINE void
DepthState::Apply(void)
{
	if (m_enable)
	{
		::glEnable(GL_DEPTH_TEST);
	}
	else
	{
		::glDisable(GL_DEPTH_TEST);
	}

	::glDepthMask(m_write);
	::glDepthFunc(m_func);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_DEPTH_STATE_INL_HPP
