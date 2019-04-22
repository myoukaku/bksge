/**
 *	@file	depth_state_inl.hpp
 *
 *	@brief	DepthState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_DEPTH_STATE_INL_HPP
#define BKSGE_RENDER_INL_DEPTH_STATE_INL_HPP

#include <bksge/render/depth_state.hpp>
#include <bksge/render/comparison_function.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
DepthState::DepthState(void)
	: m_enable(false)
	, m_write(false)
	, m_func(ComparisonFunction::kNever)
{
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_DEPTH_STATE_INL_HPP
