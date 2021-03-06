﻿/**
 *	@file	win32_game_pad_device.hpp
 *
 *	@brief	Win32GamePadDevice の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_WIN32_GAME_PAD_DEVICE_HPP
#define BKSGE_CORE_INPUT_WIN32_WIN32_GAME_PAD_DEVICE_HPP

#include <bksge/core/input/game_pad_state.hpp>
#include <bksge/core/input/win32/dinput.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/int32_t.hpp>

namespace bksge
{

namespace input
{

namespace win32
{

/**
 *	@brief	ゲームパッドデバイスのWin32版
 */
class Win32GamePadDevice
{
public:
	using State = GamePadState;

	Win32GamePadDevice(void);

	~Win32GamePadDevice();

	bool Initialize(
		IDirectInput8* direct_input,
		GUID	guid,
		HWND	hwnd,
		DWORD	coop_setting,
		bool	buffered);

	void Update(void);

	GamePadState const& state(void) const;

	static DWORD device_type(void);

private:
	void Read(void);
	void ChangePOV(DWORD rgdwPOV);

	static BOOL CALLBACK EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	static const bksge::size_t  kBufferSize  = 129;
	static const bksge::int32_t kAnalogRange = 0x7fffffff;
	static const bksge::int32_t kDeadZone    = 1000;

	GamePadState			m_state;
	IDirectInputDevice8*	m_device;
	bool					m_buffered;
};

}	// namespace win32

}	// namespace input

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/win32/inl/win32_game_pad_device_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_WIN32_WIN32_GAME_PAD_DEVICE_HPP
