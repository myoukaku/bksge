/**
 *	@file	dummy_keyboard_manager.hpp
 *
 *	@brief	DummyKeyboardManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_DUMMY_DUMMY_KEYBOARD_MANAGER_HPP
#define BKSGE_INPUT_DUMMY_DUMMY_KEYBOARD_MANAGER_HPP

#include <bksge/input/detail/keyboard_manager_base.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

class DummyKeyboardManager : public KeyboardManagerBase
{
public:
	DummyKeyboardManager(void)
	{
	}

	virtual ~DummyKeyboardManager()
	{
	}

private:
	virtual void VUpdate(void) override
	{
	}

	virtual KeyboardState const& VGetState(std::size_t /*index*/) const override
	{
		static KeyboardState const s;
		return s;
	}
};

using KeyboardManager = DummyKeyboardManager;

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_DUMMY_DUMMY_KEYBOARD_MANAGER_HPP
