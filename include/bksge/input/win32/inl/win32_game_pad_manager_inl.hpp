/**
 *	@file	win32_game_pad_manager_inl.hpp
 *
 *	@brief	Win32GamePadManager の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_INL_WIN32_GAME_PAD_MANAGER_INL_HPP
#define BKSGE_INPUT_WIN32_INL_WIN32_GAME_PAD_MANAGER_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/input/win32/win32_game_pad_manager.hpp>
#include <bksge/input/win32/win32_game_pad_device.hpp>
#include <bksge/input/win32/win32_input_manager_impl.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

namespace win32
{

class Win32GamePadManager::Impl
	: public Win32InputManagerImpl<Win32GamePadDevice>
{};

BKSGE_INLINE
Win32GamePadManager::Win32GamePadManager(void)
	: m_impl(new Impl())
{}

BKSGE_INLINE
Win32GamePadManager::~Win32GamePadManager()
{}

BKSGE_INLINE void
Win32GamePadManager::VUpdate(void)
{
	m_impl->Update();
}

BKSGE_INLINE GamePadState const&
Win32GamePadManager::VGetState(std::size_t index) const
{
	return m_impl->GetState(index);
}

}	// namespace win32

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_INPUT_WIN32_INL_WIN32_GAME_PAD_MANAGER_INL_HPP
