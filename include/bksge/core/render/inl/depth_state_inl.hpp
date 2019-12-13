/**
 *	@file	depth_state_inl.hpp
 *
 *	@brief	DepthState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_DEPTH_STATE_INL_HPP
#define BKSGE_CORE_RENDER_INL_DEPTH_STATE_INL_HPP

#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/comparison_function.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
DepthState::DepthState(void)
	: m_enable(false)
	, m_write(false)
	, m_func(ComparisonFunction::kLess)
{
}

BKSGE_INLINE bool
DepthState::enable(void) const
{
	return m_enable;
}

BKSGE_INLINE bool
DepthState::write(void) const
{
	return m_write;
}

BKSGE_INLINE ComparisonFunction
DepthState::func(void) const
{
	return m_func;
}

BKSGE_INLINE void
DepthState::SetEnable(bool enable)
{
	m_enable = enable;
}

BKSGE_INLINE void
DepthState::SetWrite(bool write)
{
	m_write = write;
}

BKSGE_INLINE void
DepthState::SetFunc(ComparisonFunction func)
{
	m_func = func;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_DEPTH_STATE_INL_HPP
