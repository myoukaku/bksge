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

BKSGE_INLINE void
StencilState::Apply(bksge::StencilState const& state)
{
	if (state.enable())
	{
		::glEnable(GL_STENCIL_TEST);
	}
	else
	{
		::glDisable(GL_STENCIL_TEST);
	}

	::glStencilFunc(
		gl::ComparisonFunction(state.func()),
		static_cast<::GLint>(state.reference()),
		static_cast<::GLuint>(state.read_mask()));
	::glStencilMask(static_cast<::GLuint>(state.write_mask()));
	::glStencilOp(
		gl::StencilOperation(state.fail_operation()),
		gl::StencilOperation(state.depth_fail_operation()),
		gl::StencilOperation(state.pass_operation()));
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_STENCIL_STATE_INL_HPP
