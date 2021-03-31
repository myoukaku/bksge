/**
 *	@file	stencil_state_inl.hpp
 *
 *	@brief	StencilState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/stencil_state.hpp>
#include <bksge/core/render/gl/detail/comparison_function.hpp>
#include <bksge/core/render/gl/detail/stencil_operation.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE
StencilState::StencilState(bksge::StencilState const& state)
	: m_enable(state.enable())
	, m_func(gl::ComparisonFunction(state.func()))
	, m_reference(static_cast<::GLint>(state.reference()))
	, m_read_mask(static_cast<::GLuint>(state.read_mask()))
	, m_write_mask(static_cast<::GLuint>(state.write_mask()))
	, m_fail_operation      (gl::StencilOperation(state.fail_operation()))
	, m_depth_fail_operation(gl::StencilOperation(state.depth_fail_operation()))
	, m_pass_operation      (gl::StencilOperation(state.pass_operation()))
{}

BKSGE_INLINE void
StencilState::Apply(void)
{
	if (m_enable)
	{
		::glEnable(GL_STENCIL_TEST);
	}
	else
	{
		::glDisable(GL_STENCIL_TEST);
	}

	::glStencilFunc(m_func, m_reference, m_read_mask);
	::glStencilMask(m_write_mask);
	::glStencilOp(m_fail_operation, m_depth_fail_operation, m_pass_operation);
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_STATE_INL_HPP
