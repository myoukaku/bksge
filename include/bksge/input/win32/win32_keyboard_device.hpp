/**
 *	@file	win32_keyboard_device.hpp
 *
 *	@brief	Win32KeyboardDevice の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_WIN32_KEYBOARD_DEVICE_HPP
#define BKSGE_INPUT_WIN32_WIN32_KEYBOARD_DEVICE_HPP

#include <bksge/input/keyboard_state.hpp>
#include <bksge/input/win32/dinput.hpp>
#include <cstddef>

namespace bksge
{

namespace input
{

/**
 *	@brief	キーボードデバイスのWin32版
 */
class Win32KeyboardDevice
{
public:
	using State = KeyboardState;

	Win32KeyboardDevice(void);

	~Win32KeyboardDevice();

	bool Initialize(
		IDirectInput8* direct_input,
		GUID	guid,
		HWND	hwnd,
		DWORD	coop_setting,
		bool	buffered);

	void Update(void);

	KeyboardState const& state(void) const;

	static DWORD device_type(void);

private:
	void ReadBuffered(void);
	void ReadNonBuffered(void);

	static const std::size_t kBufferSize = 17;	// バッファリングONのときのバッファサイズ

	KeyboardState			m_state;
	IDirectInputDevice8*	m_device;
	bool					m_buffered;
};

}	// namespace input

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/input/win32/inl/win32_keyboard_device_inl.hpp>
#endif

#endif // BKSGE_INPUT_WIN32_WIN32_KEYBOARD_DEVICE_HPP
