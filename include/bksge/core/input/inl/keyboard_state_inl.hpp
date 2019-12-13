/**
 *	@file	keyboard_state_inl.hpp
 *
 *	@brief	KeyboardState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_INL_KEYBOARD_STATE_INL_HPP
#define BKSGE_CORE_INPUT_INL_KEYBOARD_STATE_INL_HPP

#include <bksge/core/input/keyboard_state.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

BKSGE_INLINE
KeyboardState::KeyboardState(void)
	: m_keys()
{
}

BKSGE_INLINE auto
KeyboardState::pressed(KeyCode key_code) const
-> bool
{
	return m_keys[static_cast<std::size_t>(key_code)];
}

BKSGE_INLINE auto
KeyboardState::pressed(KeyCode key_code)
-> Keys::reference
{
	return m_keys[static_cast<std::size_t>(key_code)];
}

BKSGE_INLINE bool
operator==(KeyboardState const& lhs, KeyboardState const& rhs)
{
	return lhs.m_keys == rhs.m_keys;
}

BKSGE_INLINE bool
operator!=(KeyboardState const& lhs, KeyboardState const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_INL_KEYBOARD_STATE_INL_HPP
