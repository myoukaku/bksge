/**
 *	@file	game_pad_state_inl.hpp
 *
 *	@brief	GamePadState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_INL_GAME_PAD_STATE_INL_HPP
#define BKSGE_INPUT_INL_GAME_PAD_STATE_INL_HPP

#include <bksge/input/game_pad_state.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

BKSGE_INLINE
GamePadState::GamePadState(void)
	: m_buttons()
	, m_analog_buttons()
	, m_analog_sticks()
//	, m_orientation(Quaternionf::Identity())
//	, m_acceleration()
//	, m_angular_velocity()
//	, m_touch_data()
{
}

BKSGE_INLINE auto
GamePadState::pressed(std::size_t button) const
-> bool
{
	return m_buttons[button];
}

BKSGE_INLINE auto
GamePadState::pressed(std::size_t button)
-> Buttons::reference
{
	return m_buttons[button];
}

BKSGE_INLINE auto
GamePadState::analog_button(std::size_t button) const
-> AnalogButtons::const_reference
{
	return m_analog_buttons[button];
}

BKSGE_INLINE auto
GamePadState::analog_button(std::size_t button)
-> AnalogButtons::reference
{
	return m_analog_buttons[button];
}

BKSGE_INLINE auto
GamePadState::analog_stick(std::size_t stick) const
-> AnalogSticks::const_reference
{
	return m_analog_sticks[stick];
}

BKSGE_INLINE auto
GamePadState::analog_stick(std::size_t stick)
-> AnalogSticks::reference
{
	return m_analog_sticks[stick];
}

BKSGE_INLINE bool
operator==(GamePadState const& lhs, GamePadState const& rhs)
{
	return
		lhs.m_buttons        == rhs.m_buttons &&
		lhs.m_analog_buttons == rhs.m_analog_buttons &&
		lhs.m_analog_sticks  == rhs.m_analog_sticks;
}

BKSGE_INLINE bool
operator!=(GamePadState const& lhs, GamePadState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_INL_GAME_PAD_STATE_INL_HPP
