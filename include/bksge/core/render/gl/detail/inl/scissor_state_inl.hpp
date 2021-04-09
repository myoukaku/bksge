/**
 *	@file	scissor_state_inl.hpp
 *
 *	@brief	ScissorState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_SCISSOR_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_SCISSOR_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/scissor_state.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/scissor_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE void
ScissorState::Apply(bksge::ScissorState const& state)
{
	if (state.enable())
	{
		auto const& rect = state.rect();
		::glEnable(GL_SCISSOR_TEST);
		::glScissor(
			static_cast<::GLint>(rect.left()),
			static_cast<::GLint>(rect.top()),
			static_cast<::GLsizei>(rect.width()),
			static_cast<::GLsizei>(rect.height()));
	}
	else
	{
		::glDisable(GL_SCISSOR_TEST);
	}
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_SCISSOR_STATE_INL_HPP
