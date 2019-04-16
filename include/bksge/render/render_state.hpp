﻿/**
 *	@file	render_state.hpp
 *
 *	@brief	RenderState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_RENDER_STATE_HPP
#define BKSGE_RENDER_RENDER_STATE_HPP

#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/render/rasterizer_state.hpp>
#include <bksge/render/blend_state.hpp>
#include <bksge/render/depth_stencil_state.hpp>

namespace bksge
{

namespace render
{

class RenderState
{
public:
private:
	RasterizerState		m_rasterizer_state;
	BlendState			m_blend_state;
	DepthStencilState	m_depth_stencil_state;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/render_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_RENDER_STATE_HPP
