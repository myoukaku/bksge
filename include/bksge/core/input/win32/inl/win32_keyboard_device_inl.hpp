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
#include <bksge/fnd/array.hpp>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

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
	static std::unordered_map<DWORD, KeyCode> const m =
	{
		{ DIK_ESCAPE,		    KeyCode::kEscape },			    //
		{ DIK_1,				KeyCode::k1 },				    //
		{ DIK_2,				KeyCode::k2 },				    //
		{ DIK_3,				KeyCode::k3 },				    //
		{ DIK_4,				KeyCode::k4 },				    //
		{ DIK_5,				KeyCode::k5 },				    //
		{ DIK_6,				KeyCode::k6 },				    //
		{ DIK_7,				KeyCode::k7 },				    //
		{ DIK_8,				KeyCode::k8 },				    //
		{ DIK_9,				KeyCode::k9 },				    //
		{ DIK_0,				KeyCode::k0 },				    //
		{ DIK_MINUS,			KeyCode::kMinus },			    // - on main keyboard
		{ DIK_EQUALS,		    KeyCode::kEquals },			    //
		{ DIK_BACK,			    KeyCode::kBack },			    // backspace
		{ DIK_TAB,			    KeyCode::kTab },				//
		{ DIK_Q,				KeyCode::kQ },				    //
		{ DIK_W,				KeyCode::kW },				    //
		{ DIK_E,				KeyCode::kE },				    //
		{ DIK_R,				KeyCode::kR },				    //
		{ DIK_T,				KeyCode::kT },				    //
		{ DIK_Y,				KeyCode::kY },				    //
		{ DIK_U,				KeyCode::kU },				    //
		{ DIK_I,				KeyCode::kI },				    //
		{ DIK_O,				KeyCode::kO },				    //
		{ DIK_P,				KeyCode::kP },				    //
		{ DIK_LBRACKET,		    KeyCode::kLBracket },		    //
		{ DIK_RBRACKET,		    KeyCode::kRBracket },		    //
		{ DIK_RETURN,		    KeyCode::kReturn },			    // Enter on main keyboard
		{ DIK_LCONTROL,		    KeyCode::kLControl },		    //
		{ DIK_A,				KeyCode::kA },				    //
		{ DIK_S,				KeyCode::kS },				    //
		{ DIK_D,				KeyCode::kD },				    //
		{ DIK_F,				KeyCode::kF },				    //
		{ DIK_G,				KeyCode::kG },				    //
		{ DIK_H,				KeyCode::kH },				    //
		{ DIK_J,				KeyCode::kJ },				    //
		{ DIK_K,				KeyCode::kK },				    //
		{ DIK_L,				KeyCode::kL },				    //
		{ DIK_SEMICOLON,		KeyCode::kSemicolon },		    //
		{ DIK_APOSTROPHE,	    KeyCode::kApostrophe },		    //
		{ DIK_GRAVE,			KeyCode::kGrave },			    // accent grave
		{ DIK_LSHIFT,		    KeyCode::kLShift },			    //
		{ DIK_BACKSLASH,		KeyCode::kBackslash },		    //
		{ DIK_Z,				KeyCode::kZ },				    //
		{ DIK_X,				KeyCode::kX },				    //
		{ DIK_C,				KeyCode::kC },				    //
		{ DIK_V,				KeyCode::kV },				    //
		{ DIK_B,				KeyCode::kB },				    //
		{ DIK_N,				KeyCode::kN },				    //
		{ DIK_M,				KeyCode::kM },				    //
		{ DIK_COMMA,			KeyCode::kComma },			    //
		{ DIK_PERIOD,		    KeyCode::kPeriod },			    // . on main keyboard
		{ DIK_SLASH,			KeyCode::kSlash },			    // / on main keyboard
		{ DIK_RSHIFT,		    KeyCode::kRShift },			    //
		{ DIK_MULTIPLY,		    KeyCode::kMultiply },		    // * on numeric keypad
		{ DIK_LMENU,			KeyCode::kLMenu },			    // left Alt
		{ DIK_SPACE,			KeyCode::kSpace },			    //
		{ DIK_CAPITAL,		    KeyCode::kCapital },			//
		{ DIK_F1,			    KeyCode::kF1 },				    //
		{ DIK_F2,			    KeyCode::kF2 },				    //
		{ DIK_F3,			    KeyCode::kF3 },				    //
		{ DIK_F4,			    KeyCode::kF4 },				    //
		{ DIK_F5,			    KeyCode::kF5 },				    //
		{ DIK_F6,			    KeyCode::kF6 },				    //
		{ DIK_F7,			    KeyCode::kF7 },				    //
		{ DIK_F8,			    KeyCode::kF8 },				    //
		{ DIK_F9,			    KeyCode::kF9 },				    //
		{ DIK_F10,			    KeyCode::kF10 },				//
		{ DIK_NUMLOCK,		    KeyCode::kNumlock },			//
		{ DIK_SCROLL,		    KeyCode::kScroll },			    // Scroll Lock
		{ DIK_NUMPAD7,		    KeyCode::kNumpad7 },			//
		{ DIK_NUMPAD8,		    KeyCode::kNumpad8 },			//
		{ DIK_NUMPAD9,		    KeyCode::kNumpad9 },			//
		{ DIK_SUBTRACT,		    KeyCode::kSubtract },		    // - on numeric keypad
		{ DIK_NUMPAD4,		    KeyCode::kNumpad4 },			//
		{ DIK_NUMPAD5,		    KeyCode::kNumpad5 },			//
		{ DIK_NUMPAD6,		    KeyCode::kNumpad6 },			//
		{ DIK_ADD,			    KeyCode::kAdd },				// + on numeric keypad
		{ DIK_NUMPAD1,		    KeyCode::kNumpad1 },			//
		{ DIK_NUMPAD2,		    KeyCode::kNumpad2 },			//
		{ DIK_NUMPAD3,		    KeyCode::kNumpad3 },			//
		{ DIK_NUMPAD0,		    KeyCode::kNumpad0 },			//
		{ DIK_DECIMAL,		    KeyCode::kDecimal },			// . on numeric keypad
		{ DIK_OEM_102,		    KeyCode::kOem_102 },			// <> or \| on RT 102-key keyboard (Non-U.S.)
		{ DIK_F11,			    KeyCode::kF11 },				//
		{ DIK_F12,			    KeyCode::kF12 },				//
		{ DIK_F13,			    KeyCode::kF13 },				//                     (NEC PC98)
		{ DIK_F14,			    KeyCode::kF14 },				//                     (NEC PC98)
		{ DIK_F15,			    KeyCode::kF15 },				//                     (NEC PC98)
		{ DIK_KANA,			    KeyCode::kKana },			    // (Japanese keyboard)
		{ DIK_ABNT_C1,		    KeyCode::kAbnt_c1 },			// /? on Brazilian keyboard
		{ DIK_CONVERT,		    KeyCode::kConvert },			// (Japanese keyboard)
		{ DIK_NOCONVERT,		KeyCode::kNoconvert },		    // (Japanese keyboard)
		{ DIK_YEN,			    KeyCode::kYen },				// (Japanese keyboard)
		{ DIK_ABNT_C2,		    KeyCode::kAbnt_c2 },			// Numpad . on Brazilian keyboard
		{ DIK_NUMPADEQUALS,	    KeyCode::kNumpadEquals },	    // = on numeric keypad (NEC PC98)
#if defined(DIK_PREVTRACK)
		{ DIK_PREVTRACK,		KeyCode::kPrevtrack },		    // Previous Track (DIK_CIRCUMFLEX on Japanese keyboard)
#endif
		{ DIK_AT,			    KeyCode::kAt },				    //                     (NEC PC98)
		{ DIK_COLON,			KeyCode::kColon },			    //                     (NEC PC98)
		{ DIK_UNDERLINE,		KeyCode::kUnderline },		    //                     (NEC PC98)
		{ DIK_KANJI,			KeyCode::kKanji },			    // (Japanese keyboard)
		{ DIK_STOP,			    KeyCode::kStop },			    //                     (NEC PC98)
		{ DIK_AX,			    KeyCode::kAx },				    //                     (Japan AX)
		{ DIK_UNLABELED,		KeyCode::kUnlabeled },		    //                        (J3100)
		{ DIK_NEXTTRACK,		KeyCode::kNextTrack },		    // Next Track
		{ DIK_NUMPADENTER,	    KeyCode::kNumpadEnter },		// Enter on numeric keypad
		{ DIK_RCONTROL,		    KeyCode::kRControl },		    //
		{ DIK_MUTE,			    KeyCode::kMute },			    // Mute
		{ DIK_CALCULATOR,	    KeyCode::kCalculator },		    // Calculator
		{ DIK_PLAYPAUSE,		KeyCode::kPlayPause },		    // Play / Pause
		{ DIK_MEDIASTOP,		KeyCode::kMediaStop },		    // Media Stop
		{ DIK_VOLUMEDOWN,	    KeyCode::kVolumeDown },		    // Volume -
		{ DIK_VOLUMEUP,		    KeyCode::kVolumeUp },		    // Volume +
		{ DIK_WEBHOME,		    KeyCode::kWebHome },			// Web home
		{ DIK_NUMPADCOMMA,	    KeyCode::kNumpadComma },		// , on numeric keypad (NEC PC98)
		{ DIK_DIVIDE,		    KeyCode::kDivide },			    // / on numeric keypad
		{ DIK_SYSRQ,			KeyCode::kSysrq },			    //
		{ DIK_RMENU,			KeyCode::kRMenu },			    // right Alt
		{ DIK_PAUSE,			KeyCode::kPause },			    // Pause
		{ DIK_HOME,			    KeyCode::kHome },			    // Home on arrow keypad
		{ DIK_UP,			    KeyCode::kUp },				    // UpArrow on arrow keypad
		{ DIK_PRIOR,			KeyCode::kPrior },			    // PgUp on arrow keypad
		{ DIK_LEFT,			    KeyCode::kLeft },			    // LeftArrow on arrow keypad
		{ DIK_RIGHT,			KeyCode::kRight },			    // RightArrow on arrow keypad
		{ DIK_END,			    KeyCode::kEnd },				// End on arrow keypad
		{ DIK_DOWN,			    KeyCode::kDown },			    // DownArrow on arrow keypad
		{ DIK_NEXT,			    KeyCode::kNext },			    // PgDn on arrow keypad
		{ DIK_INSERT,		    KeyCode::kInsert },			    // Insert on arrow keypad
		{ DIK_DELETE,		    KeyCode::kDelete },			    // Delete on arrow keypad
		{ DIK_LWIN,			    KeyCode::kLWin },			    // Left Windows key
		{ DIK_RWIN,			    KeyCode::kRWin },			    // Right Windows key
		{ DIK_APPS,			    KeyCode::kApps },			    // AppMenu key
		{ DIK_POWER,			KeyCode::kPower },			    // System Power
		{ DIK_SLEEP,			KeyCode::kSleep },			    // System Sleep
		{ DIK_WAKE,			    KeyCode::kWake },			    // System Wake
		{ DIK_WEBSEARCH,		KeyCode::kWebSearch },		    // Web Search
		{ DIK_WEBFAVORITES,	    KeyCode::kWebFavorites },	    // Web Favorites
		{ DIK_WEBREFRESH,	    KeyCode::kWebRefresh },		    // Web Refresh
		{ DIK_WEBSTOP,		    KeyCode::kWebStop },			// Web Stop
		{ DIK_WEBFORWARD,	    KeyCode::kWebForward },		    // Web Forward
		{ DIK_WEBBACK,		    KeyCode::kWebBack },			// Web Back
		{ DIK_MYCOMPUTER,	    KeyCode::kMyComputer },		    // My Computer
		{ DIK_MAIL,			    KeyCode::kMail },			    // Mail
		{ DIK_MEDIASELECT,	    KeyCode::kMediaSelect },		// Media Select
	};

	return m.at(dik);
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

	bksge::array<std::uint8_t, 256> buffer;
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

	for (std::size_t i = 0; i < buffer.size(); ++i)
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
