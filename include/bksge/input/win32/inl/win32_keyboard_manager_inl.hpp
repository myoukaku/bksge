/**
 *	@file	win32_keyboard_manager_inl.hpp
 *
 *	@brief	Win32KeyboardManager の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_INL_WIN32_KEYBOARD_MANAGER_INL_HPP
#define BKSGE_INPUT_WIN32_INL_WIN32_KEYBOARD_MANAGER_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/input/win32/win32_keyboard_manager.hpp>
#include <bksge/input/win32/win32_keyboard_device.hpp>
#include <bksge/input/win32/win32_input_manager_impl.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

class Win32KeyboardManager::Impl
	: public Win32InputManagerImpl<Win32KeyboardDevice>
{};

BKSGE_INLINE
Win32KeyboardManager::Win32KeyboardManager(void)
	: m_impl(new Impl())
{}

BKSGE_INLINE
Win32KeyboardManager::~Win32KeyboardManager()
{}

BKSGE_INLINE void
Win32KeyboardManager::VUpdate(void)
{
	m_impl->Update();
}

BKSGE_INLINE KeyboardState const&
Win32KeyboardManager::VGetState(std::size_t index) const
{
	return m_impl->GetState(index);
}

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_INPUT_WIN32_INL_WIN32_KEYBOARD_MANAGER_INL_HPP
