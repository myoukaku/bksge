/**
 *	@file	stencil_state_inl.hpp
 *
 *	@brief	StencilState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_STENCIL_STATE_INL_HPP
#define BKSGE_CORE_RENDER_INL_STENCIL_STATE_INL_HPP

#include <bksge/core/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
StencilState::StencilState(void)
	: m_enable(false)
	, m_read_mask(0u)
	, m_write_mask(0u)
	, m_reference(0u)
	, m_func(ComparisonFunction::kNever)
	, m_fail_operation(StencilOperation::kKeep)
	, m_depth_fail_operation(StencilOperation::kKeep)
	, m_pass_operation(StencilOperation::kKeep)
{
}

BKSGE_INLINE bool
StencilState::enable(void) const
{
	return m_enable;
}

BKSGE_INLINE std::uint8_t
StencilState::read_mask(void) const
{
	return m_read_mask;
}

BKSGE_INLINE std::uint8_t
StencilState::write_mask(void) const
{
	return m_write_mask;
}

BKSGE_INLINE std::uint8_t
StencilState::reference(void) const
{
	return m_reference;
}

BKSGE_INLINE ComparisonFunction
StencilState::func(void) const
{
	return m_func;
}

BKSGE_INLINE StencilOperation
StencilState::fail_operation(void) const
{
	return m_fail_operation;
}

BKSGE_INLINE StencilOperation
StencilState::depth_fail_operation(void) const
{
	return m_depth_fail_operation;
}

BKSGE_INLINE StencilOperation
StencilState::pass_operation(void) const
{
	return m_pass_operation;
}

BKSGE_INLINE void
StencilState::SetEnable(bool enable)
{
	m_enable = enable;
}

BKSGE_INLINE void
StencilState::SetReadMask(std::uint8_t mask)
{
	m_read_mask = mask;
}

BKSGE_INLINE void
StencilState::SetWriteMask(std::uint8_t mask)
{
	m_write_mask = mask;
}

BKSGE_INLINE void
StencilState::SetReference(std::uint8_t ref)
{
	m_reference = ref;
}

BKSGE_INLINE void
StencilState::SetFunc(ComparisonFunction func)
{
	m_func = func;
}

BKSGE_INLINE void
StencilState::SetFailOperation(StencilOperation op)
{
	m_fail_operation = op;
}

BKSGE_INLINE void
StencilState::SetDepthFailOperation(StencilOperation op)
{
	m_depth_fail_operation = op;
}

BKSGE_INLINE void
StencilState::SetPassOperation(StencilOperation op)
{
	m_pass_operation = op;
}

BKSGE_INLINE bool
operator==(StencilState const& lhs, StencilState const& rhs)
{
	return
		lhs.enable()               == rhs.enable()               &&
		lhs.read_mask()            == rhs.read_mask()            &&
		lhs.write_mask()           == rhs.write_mask()           &&
		lhs.reference()            == rhs.reference()            &&
		lhs.func()                 == rhs.func()                 &&
		lhs.fail_operation()       == rhs.fail_operation()       &&
		lhs.depth_fail_operation() == rhs.depth_fail_operation() &&
		lhs.pass_operation()       == rhs.pass_operation();
}

BKSGE_INLINE bool
operator!=(StencilState const& lhs, StencilState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_STENCIL_STATE_INL_HPP
