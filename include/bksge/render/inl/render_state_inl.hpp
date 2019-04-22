﻿/**
 *	@file	render_state_inl.hpp
 *
 *	@brief	RenderState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_RENDER_STATE_INL_HPP
#define BKSGE_RENDER_INL_RENDER_STATE_INL_HPP

#include <bksge/render/render_state.hpp>
#include <bksge/render/rasterizer_state.hpp>
#include <bksge/render/blend_state.hpp>
#include <bksge/render/depth_state.hpp>
#include <bksge/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

RenderState::RenderState(void)
	: m_rasterizer_state()
	, m_blend_state()
	, m_depth_state()
	, m_stencil_state()
{
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_RENDER_STATE_INL_HPP
