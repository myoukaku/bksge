﻿/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_RASTERIZER_STATE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_RASTERIZER_STATE_HPP

#include <bksge/core/render/fwd/rasterizer_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class RasterizerState
{
public:
	static void Apply(bksge::RasterizerState const& state);
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/rasterizer_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_RASTERIZER_STATE_HPP
