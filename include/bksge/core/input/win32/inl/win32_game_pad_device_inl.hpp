/**
 *	@file	win32_game_pad_device_inl.hpp
 *
 *	@brief	Win32GamePadDevice の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_WIN32_INL_WIN32_GAME_PAD_DEVICE_INL_HPP
#define BKSGE_CORE_INPUT_WIN32_INL_WIN32_GAME_PAD_DEVICE_INL_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/core/input/win32/win32_game_pad_device.hpp>
#include <bksge/core/input/win32/diproperty.hpp>
#include <bksge/core/math/vector2.hpp>
#include <cstddef>

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

namespace detail
{

enum
{
	kWin32GamePad_AnalogStick_Left,
	kWin32GamePad_AnalogStick_Right,
};

enum
{
	kWin32GamePad_AnalogButton_Left,
	kWin32GamePad_AnalogButton_Right,
};

enum
{
	kWin32GamePad_Direction_Left,
	kWin32GamePad_Direction_Down,
	kWin32GamePad_Direction_Right,
	kWin32GamePad_Direction_Up,

	kWin32GamePad_Direction_Max,
};

}	// namespace detail

BKSGE_INLINE
Win32GamePadDevice::Win32GamePadDevice(void)
	: m_device(nullptr)
	, m_buffered(false)
{
}

BKSGE_INLINE bool
Win32GamePadDevice::Initialize(
	IDirectInput8* direct_input,
	GUID	guid,
	HWND	hwnd,
	DWORD	coop_setting,
	bool	buffered)
{
	IDirectInputDevice8* device;
	HRESULT hr = direct_input->CreateDevice(guid, &device, nullptr);

	if (FAILED(hr))
	{
		// TODO	エラー処理
		return false;
	}

	hr = device->SetDataFormat(&c_dfDIJoystick2);

	if (FAILED(hr))
	{
		// TODO	エラー処理
		return false;
	}

	if (hwnd)
	{
		hr = device->SetCooperativeLevel(hwnd, coop_setting);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return false;
		}
	}

	//if (buffered)
	{
		DIProperty dipdw;
		dipdw.diph.dwHow	= DIPH_DEVICE;
		dipdw.dwData		= kBufferSize;

		hr = device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return false;
		}
	}

	device->EnumObjects(EnumObjectsCallback, device, DIDFT_AXIS);

	hr = device->Acquire();

	if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
	{
		// TODO	エラー処理
		return false;
	}

	m_device = device;
	m_buffered = buffered;
	return true;
}

BKSGE_INLINE BOOL CALLBACK
Win32GamePadDevice::EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	auto device = reinterpret_cast<IDirectInputDevice8*>(pvRef);

    LONG    min = -kAnalogRange;
    LONG    max =  kAnalogRange;
	DWORD	dead_zone = kDeadZone;

	if (lpddoi->guidType == GUID_RxAxis ||
		lpddoi->guidType == GUID_RyAxis)
	{
		min       = 0;
		max       = kAnalogRange;
		dead_zone = 0;
	}

	{
		DIPropertyRange diprg;
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = lpddoi->dwType;
		diprg.lMin       = min;
		diprg.lMax       = max;

		HRESULT hr = device->SetProperty(DIPROP_RANGE, &diprg.diph);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return DIENUM_CONTINUE;
		}
	}
	{
		DIProperty dipdw;
		dipdw.diph.dwHow = DIPH_BYID;
		dipdw.diph.dwObj = lpddoi->dwType;
		dipdw.dwData     = dead_zone;

		HRESULT hr = device->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return DIENUM_CONTINUE;
		}
	}

	return DIENUM_CONTINUE;
}

BKSGE_INLINE
Win32GamePadDevice::~Win32GamePadDevice()
{
	if (m_device)
	{
		m_device->Unacquire();
		m_device->Release();
		m_device = nullptr;
	}
}

BKSGE_INLINE void
Win32GamePadDevice::Update(void)
{
	Read();
}

BKSGE_INLINE GamePadState const&
Win32GamePadDevice::state(void) const
{
	return m_state;
}

BKSGE_INLINE DWORD
Win32GamePadDevice::device_type(void)
{
	return DI8DEVCLASS_GAMECTRL;
}

BKSGE_INLINE void
Win32GamePadDevice::Read(void)
{
	m_state = GamePadState();

	if (!m_device)
	{
		return;
	}

	DIJOYSTATE2 joystate = {};

	HRESULT hr = m_device->Poll();

	if (hr == DI_OK)
	{
		hr = m_device->GetDeviceState(sizeof(joystate), &joystate);
	}

	if (hr != DI_OK)
	{
		hr = m_device->Acquire();

		while (hr == DIERR_INPUTLOST)
		{
			hr = m_device->Acquire();
		}

		m_device->Poll();
		hr = m_device->GetDeviceState(sizeof(joystate), &joystate);

		if (FAILED(hr))
		{
			return;
		}
	}

	auto const analog_range = static_cast<float>(kAnalogRange);
	{
		auto const lx = static_cast<float>(joystate.lX);
		auto const ly = static_cast<float>(joystate.lY);
		m_state.analog_stick(detail::kWin32GamePad_AnalogStick_Left) = bksge::Vector2f(lx, ly) / analog_range;
	}
	{
		auto const rx = static_cast<float>(joystate.lZ);
		auto const ry = static_cast<float>(joystate.lRz);
		m_state.analog_stick(detail::kWin32GamePad_AnalogStick_Right) = bksge::Vector2f(rx, ry) / analog_range;
	}
	{
		auto const lz = static_cast<float>(joystate.lRx);
		m_state.analog_button(detail::kWin32GamePad_AnalogButton_Left) = lz / analog_range;
	}
	{
		auto const rz = static_cast<float>(joystate.lRy);
		m_state.analog_button(detail::kWin32GamePad_AnalogButton_Right) = rz / analog_range;
	}

	ChangePOV(joystate.rgdwPOV[0]);

	for (std::size_t i = 0; i < m_state.kButtonMax - detail::kWin32GamePad_Direction_Max; i++)
	{
		if ((joystate.rgbButtons[i] & 0x80) != 0)
		{
			m_state.pressed(i + detail::kWin32GamePad_Direction_Max) = true;
		}
	}
}

BKSGE_INLINE void
Win32GamePadDevice::ChangePOV(DWORD rgdwPOV)
{
	if (LOWORD(rgdwPOV) == 0xFFFF)
	{
		return;
	}

	if (rgdwPOV < 9000 || 27000 < rgdwPOV)
	{
		m_state.pressed(detail::kWin32GamePad_Direction_Up) = true;
	}

	if (0 < rgdwPOV && rgdwPOV < 18000)
	{
		m_state.pressed(detail::kWin32GamePad_Direction_Right) = true;
	}

	if (9000 < rgdwPOV && rgdwPOV < 27000)
	{
		m_state.pressed(detail::kWin32GamePad_Direction_Down) = true;
	}

	if (18000 < rgdwPOV && rgdwPOV < 36000)
	{
		m_state.pressed(detail::kWin32GamePad_Direction_Left) = true;
	}
}

}	// namespace win32

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_CORE_INPUT_WIN32_INL_WIN32_GAME_PAD_DEVICE_INL_HPP
