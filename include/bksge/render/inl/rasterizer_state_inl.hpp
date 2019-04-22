/**
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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_RASTERIZER_STATE_INL_HPP
