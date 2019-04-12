﻿/**
 *	@file	win32_mouse_manager_inl.hpp
 *
 *	@brief	Win32MouseManager の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_INL_WIN32_MOUSE_MANAGER_INL_HPP
#define BKSGE_INPUT_WIN32_INL_WIN32_MOUSE_MANAGER_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/input/win32/win32_mouse_manager.hpp>
#include <bksge/input/win32/win32_mouse_device.hpp>
#include <bksge/input/win32/win32_input_manager_impl.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

class Win32MouseManager::Impl
	: public Win32InputManagerImpl<Win32MouseDevice>
{};

BKSGE_INLINE
Win32MouseManager::Win32MouseManager(void)
	: m_impl(new Impl())
{}

BKSGE_INLINE
Win32MouseManager::~Win32MouseManager()
{}

BKSGE_INLINE void
Win32MouseManager::VUpdate(void)
{
	m_impl->Update();
}

BKSGE_INLINE MouseState const&
Win32MouseManager::VGetState(std::size_t index) const
{
	return m_impl->GetState(index);
}

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_INPUT_WIN32_INL_WIN32_MOUSE_MANAGER_INL_HPP