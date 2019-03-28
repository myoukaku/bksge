/**
 *	@file	win32_keyboard_manager.hpp
 *
 *	@brief	Win32KeyboardManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_WIN32_KEYBOARD_MANAGER_HPP
#define BKSGE_INPUT_WIN32_WIN32_KEYBOARD_MANAGER_HPP

#include <bksge/input/detail/keyboard_manager_base.hpp>
#include <cstddef>
#include <memory>

namespace bksge
{

namespace input
{

/**
 *	@brief	Win32版のKeyboardManager
 */
class Win32KeyboardManager : public KeyboardManagerBase
{
public:
	Win32KeyboardManager(void);

	virtual ~Win32KeyboardManager();

private:
	virtual void VUpdate(void) override;

	virtual KeyboardState const& VGetState(std::size_t index) const override;

	class Impl;
	std::unique_ptr<Impl>	m_impl;
};

using KeyboardManager = Win32KeyboardManager;

}	// namespace input

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/input/win32/inl/win32_keyboard_manager_inl.hpp>
#endif

#endif // BKSGE_INPUT_WIN32_WIN32_KEYBOARD_MANAGER_HPP
