/**
 *	@file	win32_direct_input_inl.hpp
 *
 *	@brief	Win32DirectInput の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_INL_WIN32_DIRECT_INPUT_INL_HPP
#define BKSGE_CORE_INPUT_WIN32_INL_WIN32_DIRECT_INPUT_INL_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/core/input/win32/win32_direct_input.hpp>
#include <bksge/core/detail/win32.hpp>

#if defined(_MSC_VER)
#	pragma comment (lib, "dinput8.lib")
#	pragma comment (lib, "dxguid.lib")
#endif

namespace bksge
{

namespace input
{

namespace win32
{

BKSGE_INLINE
Win32DirectInput::Win32DirectInput(void)
	: m_direct_input(nullptr)
{
	HINSTANCE const hinstance = bksge::win32::GetModuleHandle<char>(nullptr);
	HRESULT const hr =
		::DirectInput8Create(
			hinstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			reinterpret_cast<VOID**>(&m_direct_input),
			nullptr);

	if (FAILED(hr))
	{
		return;
	}
}

BKSGE_INLINE
Win32DirectInput::~Win32DirectInput()
{
	if (m_direct_input)
	{
		m_direct_input->Release();
		m_direct_input = nullptr;
	}
}

BKSGE_INLINE IDirectInput8*
Win32DirectInput::get(void)
{
	static Win32DirectInput	s_instance;
	return s_instance.m_direct_input;
}

}	// namespace win32

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_CORE_INPUT_WIN32_INL_WIN32_DIRECT_INPUT_INL_HPP
