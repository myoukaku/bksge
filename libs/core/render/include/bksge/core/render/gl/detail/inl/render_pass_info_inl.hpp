/**
 *	@file	render_pass_info_inl.hpp
 *
 *	@brief	RenderPassInfo クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_PASS_INFO_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_PASS_INFO_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/render_pass_info.hpp>
#include <bksge/core/render/gl/detail/clear_state.hpp>
#include <bksge/core/render/gl/detail/viewport.hpp>
#include <bksge/core/render/gl/detail/scissor_state.hpp>
#include <bksge/core/render/render_pass_info.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE void
RenderPassInfo::Apply(bksge::RenderPassInfo const& info)
{
	gl::ClearState::Apply(info.clear_state());
	gl::Viewport::Apply(info.viewport());
	gl::ScissorState::Apply(info.scissor_state());
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RENDER_PASS_INFO_INL_HPP
