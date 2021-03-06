﻿/**
 *	@file	rasterizer_state_inl.hpp
 *
 *	@brief	RasterizerState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_RASTERIZER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_RASTERIZER_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/rasterizer_state.hpp>
#include <bksge/core/render/gl/detail/cull_mode.hpp>
#include <bksge/core/render/gl/detail/front_face.hpp>
#include <bksge/core/render/gl/detail/fill_mode.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>
#include <bksge/core/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

BKSGE_INLINE void
RasterizerState::Apply(bksge::RasterizerState const& state)
{
	if (state.cull_mode() != bksge::CullMode::kNone)
	{
		::glEnable(GL_CULL_FACE);
		::glCullFace(gl::CullMode(state.cull_mode()));
	}
	else
	{
		::glDisable(GL_CULL_FACE);
	}

	::glFrontFace(gl::FrontFace(state.front_face()));
	::glPolygonMode(GL_FRONT_AND_BACK, gl::FillMode(state.fill_mode()));
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_RASTERIZER_STATE_INL_HPP
