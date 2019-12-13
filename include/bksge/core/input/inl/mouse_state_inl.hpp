/**
 *	@file	mouse_state_inl.hpp
 *
 *	@brief	MouseState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_INL_MOUSE_STATE_INL_HPP
#define BKSGE_CORE_INPUT_INL_MOUSE_STATE_INL_HPP

#include <bksge/core/input/mouse_state.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

BKSGE_INLINE
MouseState::MouseState(void)
	: m_buttons()
	, m_velocities()
{
}

BKSGE_INLINE auto
MouseState::pressed(MouseButton button) const
-> bool
{
	return m_buttons[static_cast<std::size_t>(button)];
}

BKSGE_INLINE auto
MouseState::pressed(MouseButton button)
-> Buttons::reference
{
	return m_buttons[static_cast<std::size_t>(button)];
}

BKSGE_INLINE auto
MouseState::velocity(MouseAxis axis) const
-> float
{
	return m_velocities[static_cast<std::size_t>(axis)];
}

BKSGE_INLINE auto
MouseState::velocity(MouseAxis axis)
-> Velocities::reference
{
	return m_velocities[static_cast<std::size_t>(axis)];
}

BKSGE_INLINE auto
MouseState::buttons(void) const
-> Buttons const&
{
	return m_buttons;
}

BKSGE_INLINE auto
MouseState::buttons(void)
-> Buttons&
{
	return m_buttons;
}

BKSGE_INLINE bool
operator==(MouseState const& lhs, MouseState const& rhs)
{
	return
		lhs.m_buttons    == rhs.m_buttons &&
		lhs.m_velocities == rhs.m_velocities;
}

BKSGE_INLINE bool
operator!=(MouseState const& lhs, MouseState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_INL_MOUSE_STATE_INL_HPP
