/**
 *	@file	win32_keyboard_manager.hpp
 *
 *	@brief	Win32KeyboardManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_WIN32_KEYBOARD_MANAGER_HPP
#define BKSGE_CORE_INPUT_WIN32_WIN32_KEYBOARD_MANAGER_HPP

#include <bksge/core/input/detail/keyboard_manager_base.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <memory>

namespace bksge
{

namespace input
{

namespace win32
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
	void VUpdate(void) override;

	KeyboardState const& VGetState(bksge::size_t index) const override;

	class Impl;
	std::unique_ptr<Impl>	m_impl;
};

}	// namespace win32

using KeyboardManager = win32::Win32KeyboardManager;

}	// namespace input

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/win32/inl/win32_keyboard_manager_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_WIN32_WIN32_KEYBOARD_MANAGER_HPP
