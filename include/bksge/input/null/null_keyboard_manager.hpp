/**
 *	@file	null_keyboard_manager.hpp
 *
 *	@brief	NullKeyboardManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_NULL_NULL_KEYBOARD_MANAGER_HPP
#define BKSGE_INPUT_NULL_NULL_KEYBOARD_MANAGER_HPP

#include <bksge/input/detail/keyboard_manager_base.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

class NullKeyboardManager : public KeyboardManagerBase
{
public:
	NullKeyboardManager(void)
	{
	}

	virtual ~NullKeyboardManager()
	{
	}

private:
	void VUpdate(void) override
	{
	}

	KeyboardState const& VGetState(std::size_t /*index*/) const override
	{
		static KeyboardState const s;
		return s;
	}
};

using KeyboardManager = NullKeyboardManager;

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_NULL_NULL_KEYBOARD_MANAGER_HPP
