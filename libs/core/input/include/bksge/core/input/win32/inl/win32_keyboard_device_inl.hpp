/**
 *	@file	win32_keyboard_device_inl.hpp
 *
 *	@brief	Win32KeyboardDevice の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_INL_WIN32_KEYBOARD_DEVICE_INL_HPP
#define BKSGE_CORE_INPUT_WIN32_INL_WIN32_KEYBOARD_DEVICE_INL_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/core/input/win32/win32_keyboard_device.hpp>
#include <bksge/core/input/win32/diproperty.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/array.hpp>

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

///////////////////////////////////////////////////////////////////////////////
//
//	非メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
namespace detail
{

inline KeyCode DIKtoKeyCode(DWORD dik)
{
	switch (dik)
	{
	case DIK_ESCAPE:		    return KeyCode::kEscape;			//
	case DIK_1:				    return KeyCode::k1;				    //
	case DIK_2:				    return KeyCode::k2;				    //
	case DIK_3:				    return KeyCode::k3;				    //
	case DIK_4:				    return KeyCode::k4;				    //
	case DIK_5:				    return KeyCode::k5;				    //
	case DIK_6:				    return KeyCode::k6;				    //
	case DIK_7:				    return KeyCode::k7;				    //
	case DIK_8:				    return KeyCode::k8;				    //
	case DIK_9:				    return KeyCode::k9;				    //
	case DIK_0:				    return KeyCode::k0;				    //
	case DIK_MINUS:			    return KeyCode::kMinus;			    // - on main keyboard
	case DIK_EQUALS:		    return KeyCode::kEquals;			//
	case DIK_BACK:			    return KeyCode::kBack;			    // backspace
	case DIK_TAB:			    return KeyCode::kTab;				//
	case DIK_Q:				    return KeyCode::kQ;				    //
	case DIK_W:				    return KeyCode::kW;				    //
	case DIK_E:				    return KeyCode::kE;				    //
	case DIK_R:				    return KeyCode::kR;				    //
	case DIK_T:				    return KeyCode::kT;				    //
	case DIK_Y:				    return KeyCode::kY;				    //
	case DIK_U:				    return KeyCode::kU;				    //
	case DIK_I:				    return KeyCode::kI;				    //
	case DIK_O:				    return KeyCode::kO;				    //
	case DIK_P:				    return KeyCode::kP;				    //
	case DIK_LBRACKET:		    return KeyCode::kLBracket;		    //
	case DIK_RBRACKET:		    return KeyCode::kRBracket;		    //
	case DIK_RETURN:		    return KeyCode::kReturn;			// Enter on main keyboard
	case DIK_LCONTROL:		    return KeyCode::kLControl;		    //
	case DIK_A:				    return KeyCode::kA;				    //
	case DIK_S:				    return KeyCode::kS;				    //
	case DIK_D:				    return KeyCode::kD;				    //
	case DIK_F:				    return KeyCode::kF;				    //
	case DIK_G:				    return KeyCode::kG;				    //
	case DIK_H:				    return KeyCode::kH;				    //
	case DIK_J:				    return KeyCode::kJ;				    //
	case DIK_K:				    return KeyCode::kK;				    //
	case DIK_L:				    return KeyCode::kL;				    //
	case DIK_SEMICOLON:		    return KeyCode::kSemicolon;		    //
	case DIK_APOSTROPHE:	    return KeyCode::kApostrophe;		//
	case DIK_GRAVE:			    return KeyCode::kGrave;			    // accent grave
	case DIK_LSHIFT:		    return KeyCode::kLShift;			//
	case DIK_BACKSLASH:		    return KeyCode::kBackslash;		    //
	case DIK_Z:				    return KeyCode::kZ;				    //
	case DIK_X:				    return KeyCode::kX;				    //
	case DIK_C:				    return KeyCode::kC;				    //
	case DIK_V:				    return KeyCode::kV;				    //
	case DIK_B:				    return KeyCode::kB;				    //
	case DIK_N:				    return KeyCode::kN;				    //
	case DIK_M:				    return KeyCode::kM;				    //
	case DIK_COMMA:			    return KeyCode::kComma;			    //
	case DIK_PERIOD:		    return KeyCode::kPeriod;			// . on main keyboard
	case DIK_SLASH:			    return KeyCode::kSlash;			    // / on main keyboard
	case DIK_RSHIFT:		    return KeyCode::kRShift;			//
	case DIK_MULTIPLY:		    return KeyCode::kMultiply;		    // * on numeric keypad
	case DIK_LMENU:			    return KeyCode::kLMenu;			    // left Alt
	case DIK_SPACE:			    return KeyCode::kSpace;			    //
	case DIK_CAPITAL:		    return KeyCode::kCapital;			//
	case DIK_F1:			    return KeyCode::kF1;				//
	case DIK_F2:			    return KeyCode::kF2;				//
	case DIK_F3:			    return KeyCode::kF3;				//
	case DIK_F4:			    return KeyCode::kF4;				//
	case DIK_F5:			    return KeyCode::kF5;				//
	case DIK_F6:			    return KeyCode::kF6;				//
	case DIK_F7:			    return KeyCode::kF7;				//
	case DIK_F8:			    return KeyCode::kF8;				//
	case DIK_F9:			    return KeyCode::kF9;				//
	case DIK_F10:			    return KeyCode::kF10;				//
	case DIK_NUMLOCK:		    return KeyCode::kNumlock;			//
	case DIK_SCROLL:		    return KeyCode::kScroll;			// Scroll Lock
	case DIK_NUMPAD7:		    return KeyCode::kNumpad7;			//
	case DIK_NUMPAD8:		    return KeyCode::kNumpad8;			//
	case DIK_NUMPAD9:		    return KeyCode::kNumpad9;			//
	case DIK_SUBTRACT:		    return KeyCode::kSubtract;		    // - on numeric keypad
	case DIK_NUMPAD4:		    return KeyCode::kNumpad4;			//
	case DIK_NUMPAD5:		    return KeyCode::kNumpad5;			//
	case DIK_NUMPAD6:		    return KeyCode::kNumpad6;			//
	case DIK_ADD:			    return KeyCode::kAdd;				// + on numeric keypad
	case DIK_NUMPAD1:		    return KeyCode::kNumpad1;			//
	case DIK_NUMPAD2:		    return KeyCode::kNumpad2;			//
	case DIK_NUMPAD3:		    return KeyCode::kNumpad3;			//
	case DIK_NUMPAD0:		    return KeyCode::kNumpad0;			//
	case DIK_DECIMAL:		    return KeyCode::kDecimal;			// . on numeric keypad
	case DIK_OEM_102:		    return KeyCode::kOem_102;			// <> or \| on RT 102-key keyboard (Non-U.S.)
	case DIK_F11:			    return KeyCode::kF11;				//
	case DIK_F12:			    return KeyCode::kF12;				//
	case DIK_F13:			    return KeyCode::kF13;				//                     (NEC PC98)
	case DIK_F14:			    return KeyCode::kF14;				//                     (NEC PC98)
	case DIK_F15:			    return KeyCode::kF15;				//                     (NEC PC98)
	case DIK_KANA:			    return KeyCode::kKana;			    // (Japanese keyboard)
	case DIK_ABNT_C1:		    return KeyCode::kAbnt_c1;			// /? on Brazilian keyboard
	case DIK_CONVERT:		    return KeyCode::kConvert;			// (Japanese keyboard)
	case DIK_NOCONVERT:		    return KeyCode::kNoconvert;		    // (Japanese keyboard)
	case DIK_YEN:			    return KeyCode::kYen;				// (Japanese keyboard)
	case DIK_ABNT_C2:		    return KeyCode::kAbnt_c2;			// Numpad . on Brazilian keyboard
	case DIK_NUMPADEQUALS:	    return KeyCode::kNumpadEquals;	    // = on numeric keypad (NEC PC98)
#if defined(DIK_PREVTRACK)
	case DIK_PREVTRACK:		    return KeyCode::kPrevtrack;		    // Previous Track (DIK_CIRCUMFLEX on Japanese keyboard)
#endif
	case DIK_AT:			    return KeyCode::kAt;				//                     (NEC PC98)
	case DIK_COLON:			    return KeyCode::kColon;			    //                     (NEC PC98)
	case DIK_UNDERLINE:		    return KeyCode::kUnderline;		    //                     (NEC PC98)
	case DIK_KANJI:			    return KeyCode::kKanji;			    // (Japanese keyboard)
	case DIK_STOP:			    return KeyCode::kStop;			    //                     (NEC PC98)
	case DIK_AX:			    return KeyCode::kAx;				//                     (Japan AX)
	case DIK_UNLABELED:		    return KeyCode::kUnlabeled;		    //                        (J3100)
	case DIK_NEXTTRACK:		    return KeyCode::kNextTrack;		    // Next Track
	case DIK_NUMPADENTER:	    return KeyCode::kNumpadEnter;		// Enter on numeric keypad
	case DIK_RCONTROL:		    return KeyCode::kRControl;		    //
	case DIK_MUTE:			    return KeyCode::kMute;			    // Mute
	case DIK_CALCULATOR:	    return KeyCode::kCalculator;		// Calculator
	case DIK_PLAYPAUSE:		    return KeyCode::kPlayPause;		    // Play / Pause
	case DIK_MEDIASTOP:		    return KeyCode::kMediaStop;		    // Media Stop
	case DIK_VOLUMEDOWN:	    return KeyCode::kVolumeDown;		// Volume -
	case DIK_VOLUMEUP:		    return KeyCode::kVolumeUp;		    // Volume +
	case DIK_WEBHOME:		    return KeyCode::kWebHome;			// Web home
	case DIK_NUMPADCOMMA:	    return KeyCode::kNumpadComma;		// , on numeric keypad (NEC PC98)
	case DIK_DIVIDE:		    return KeyCode::kDivide;			// / on numeric keypad
	case DIK_SYSRQ:			    return KeyCode::kSysrq;			    //
	case DIK_RMENU:			    return KeyCode::kRMenu;			    // right Alt
	case DIK_PAUSE:			    return KeyCode::kPause;			    // Pause
	case DIK_HOME:			    return KeyCode::kHome;			    // Home on arrow keypad
	case DIK_UP:			    return KeyCode::kUp;				// UpArrow on arrow keypad
	case DIK_PRIOR:			    return KeyCode::kPrior;			    // PgUp on arrow keypad
	case DIK_LEFT:			    return KeyCode::kLeft;			    // LeftArrow on arrow keypad
	case DIK_RIGHT:			    return KeyCode::kRight;			    // RightArrow on arrow keypad
	case DIK_END:			    return KeyCode::kEnd;				// End on arrow keypad
	case DIK_DOWN:			    return KeyCode::kDown;			    // DownArrow on arrow keypad
	case DIK_NEXT:			    return KeyCode::kNext;			    // PgDn on arrow keypad
	case DIK_INSERT:		    return KeyCode::kInsert;			// Insert on arrow keypad
	case DIK_DELETE:		    return KeyCode::kDelete;			// Delete on arrow keypad
	case DIK_LWIN:			    return KeyCode::kLWin;			    // Left Windows key
	case DIK_RWIN:			    return KeyCode::kRWin;			    // Right Windows key
	case DIK_APPS:			    return KeyCode::kApps;			    // AppMenu key
	case DIK_POWER:			    return KeyCode::kPower;			    // System Power
	case DIK_SLEEP:			    return KeyCode::kSleep;			    // System Sleep
	case DIK_WAKE:			    return KeyCode::kWake;			    // System Wake
	case DIK_WEBSEARCH:		    return KeyCode::kWebSearch;		    // Web Search
	case DIK_WEBFAVORITES:	    return KeyCode::kWebFavorites;	    // Web Favorites
	case DIK_WEBREFRESH:	    return KeyCode::kWebRefresh;		// Web Refresh
	case DIK_WEBSTOP:		    return KeyCode::kWebStop;			// Web Stop
	case DIK_WEBFORWARD:	    return KeyCode::kWebForward;		// Web Forward
	case DIK_WEBBACK:		    return KeyCode::kWebBack;			// Web Back
	case DIK_MYCOMPUTER:	    return KeyCode::kMyComputer;		// My Computer
	case DIK_MAIL:			    return KeyCode::kMail;			    // Mail
	case DIK_MEDIASELECT:	    return KeyCode::kMediaSelect;		// Media Select
	}

	return KeyCode::kUnassigned;
}

}	// namespace detail

///////////////////////////////////////////////////////////////////////////////
//
//	メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
Win32KeyboardDevice::Win32KeyboardDevice(void)
	: m_device(nullptr)
	, m_buffered(false)
{}

BKSGE_INLINE bool
Win32KeyboardDevice::Initialize(
	IDirectInput8* direct_input,
	GUID	guid,
	HWND	hwnd,
	DWORD	coop_setting,
	bool	buffered)
{
	IDirectInputDevice8* keyboard;
	HRESULT hr = direct_input->CreateDevice(guid, &keyboard, nullptr);

	if (FAILED(hr))
	{
		// TODO	エラー処理
		return false;
	}

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr))
	{
		// TODO	エラー処理
		return false;
	}

	if (hwnd)
	{
		hr = keyboard->SetCooperativeLevel(hwnd, coop_setting);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return false;
		}
	}

	if (buffered)
	{
		DIProperty dipdw;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData	 = kBufferSize;

		hr = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return false;
		}
	}

	hr = keyboard->Acquire();

	if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
	{
		// TODO	エラー処理
		return false;
	}

	m_device = keyboard;
	m_buffered = buffered;
	return true;
}

BKSGE_INLINE
Win32KeyboardDevice::~Win32KeyboardDevice()
{
	if (m_device)
	{
		m_device->Unacquire();
		m_device->Release();
		m_device = nullptr;
	}
}

BKSGE_INLINE void
Win32KeyboardDevice::Update(void)
{
	if (m_buffered)
	{
		ReadBuffered();
	}
	else
	{
		ReadNonBuffered();
	}
}

BKSGE_INLINE KeyboardState const&
Win32KeyboardDevice::state(void) const
{
	return m_state;
}

BKSGE_INLINE DWORD
Win32KeyboardDevice::device_type(void)
{
	return DI8DEVCLASS_KEYBOARD;
}

BKSGE_INLINE void
Win32KeyboardDevice::ReadBuffered(void)
{
	DIDEVICEOBJECTDATA di_buff[kBufferSize];
	DWORD entries = kBufferSize;
	HRESULT hr = m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), di_buff, &entries, 0);

	if (FAILED(hr))
	{
		// TODO エラー処理

		hr = m_device->Acquire();

		if (hr == E_ACCESSDENIED)
		{
			//verify_after_alt_tab = true;
		}

		while (hr == DIERR_INPUTLOST)
		{
			hr = m_device->Acquire();
		}

		return;
	}

	for (DWORD i = 0; i < entries; ++i)
	{
		DWORD const dik = di_buff[i].dwOfs;
		KeyCode const kc = detail::DIKtoKeyCode(dik);
		bool const pressed = ((di_buff[i].dwData & 0x80) != 0);
		m_state.pressed(kc) = pressed;
	}
}

BKSGE_INLINE void
Win32KeyboardDevice::ReadNonBuffered(void)
{
	m_state = KeyboardState();

	bksge::array<bksge::uint8_t, 256> buffer;
	HRESULT hr = m_device->GetDeviceState(sizeof(buffer), buffer.data());

	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	{
		hr = m_device->Acquire();

		if (hr != DIERR_OTHERAPPHASPRIO)
		{
			hr = m_device->GetDeviceState(sizeof(buffer), buffer.data());
		}
	}

	if (FAILED(hr))
	{
		return;
	}

	for (bksge::size_t i = 0; i < buffer.size(); ++i)
	{
		if ((buffer[i] & 0x80) != 0)
		{
			KeyCode const kc = detail::DIKtoKeyCode(static_cast<DWORD>(i));
			m_state.pressed(kc) = true;
		}
	}
}

}	// namespace win32

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_CORE_INPUT_WIN32_INL_WIN32_KEYBOARD_DEVICE_INL_HPP
