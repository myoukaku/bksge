﻿/**
 *	@file	win32_mouse_device.hpp
 *
 *	@brief	Win32MouseDevice の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_WIN32_MOUSE_DEVICE_HPP
#define BKSGE_CORE_INPUT_WIN32_WIN32_MOUSE_DEVICE_HPP

#include <bksge/core/input/mouse_state.hpp>
#include <bksge/core/input/win32/dinput.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace input
{

namespace win32
{

/**
 *	@brief	マウスデバイスのWin32版
 */
class Win32MouseDevice
{
public:
	using State = MouseState;

	Win32MouseDevice(void);

	~Win32MouseDevice();

	bool Initialize(
		IDirectInput8* direct_input,
		GUID	guid,
		HWND	hwnd,
		DWORD	coop_setting,
		bool	buffered);

	void Update(void);

	MouseState const& state(void) const;

	static DWORD device_type(void);

private:
	void Read(void);

	static const bksge::size_t kBufferSize = 128;

	MouseState				m_state;
	IDirectInputDevice8*	m_device;
	int						m_granularity_z;
	bool					m_buffered;
	HWND					m_hwnd;
	DWORD					m_coop_setting;
};

}	// namespace win32

}	// namespace input

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/win32/inl/win32_mouse_device_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_WIN32_WIN32_MOUSE_DEVICE_HPP
