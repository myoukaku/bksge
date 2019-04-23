﻿/**
 *	@file	rasterizer_state_inl.hpp
 *
 *	@brief	RasterizerState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_RASTERIZER_STATE_INL_HPP
#define BKSGE_RENDER_INL_RASTERIZER_STATE_INL_HPP

#include <bksge/render/rasterizer_state.hpp>
#include <bksge/render/fill_mode.hpp>
#include <bksge/render/cull_mode.hpp>
#include <bksge/render/front_face.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
RasterizerState::RasterizerState(void)
	: m_fill_mode(FillMode::kSolid)
	, m_cull_mode(CullMode::kNone)
	, m_front_face(FrontFace::kClockwise)
{
}

BKSGE_INLINE FillMode
RasterizerState::fill_mode(void) const
{
	return m_fill_mode;
}

BKSGE_INLINE CullMode
RasterizerState::cull_mode(void) const
{
	return m_cull_mode;
}

BKSGE_INLINE FrontFace
RasterizerState::front_face(void) const
{
	return m_front_face;
}

BKSGE_INLINE void
RasterizerState::SetFillMode(FillMode fill_mode)
{
	m_fill_mode = fill_mode;
}

BKSGE_INLINE void
RasterizerState::SetCullMode(CullMode cull_mode)
{
	m_cull_mode = cull_mode;
}

BKSGE_INLINE void
RasterizerState::SetFrontFace(FrontFace front_face)
{
	m_front_face = front_face;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_RASTERIZER_STATE_INL_HPP
