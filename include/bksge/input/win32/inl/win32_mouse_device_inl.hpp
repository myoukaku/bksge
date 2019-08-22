/**
 *	@file	win32_mouse_device_inl.hpp
 *
 *	@brief	Win32MouseDevice の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_INL_WIN32_MOUSE_DEVICE_INL_HPP
#define BKSGE_INPUT_WIN32_INL_WIN32_MOUSE_DEVICE_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/input/win32/win32_mouse_device.hpp>
#include <bksge/input/win32/diproperty.hpp>
#include <type_traits>
#include <unordered_map>

#if defined(_MSC_VER)
#	pragma comment (lib, "dinput8.lib")
#	pragma comment (lib, "dxguid.lib")
#endif

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4644);

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

inline MouseButton DIMOfsToMouseButton(DWORD ofs)
{
	static std::unordered_map<DWORD, MouseButton> const m =
	{
		{ DIMOFS_BUTTON0,	MouseButton::k0 },
		{ DIMOFS_BUTTON1,	MouseButton::k1 },
		{ DIMOFS_BUTTON2,	MouseButton::k2 },
		{ DIMOFS_BUTTON3,	MouseButton::k3 },
		{ DIMOFS_BUTTON4,	MouseButton::k4 },
		{ DIMOFS_BUTTON5,	MouseButton::k5 },
		{ DIMOFS_BUTTON6,	MouseButton::k6 },
		{ DIMOFS_BUTTON7,	MouseButton::k7 },
	};

	return m.at(ofs);
}

inline MouseAxis DIMOfsToMouseAxis(DWORD ofs)
{
	static std::unordered_map<DWORD, MouseAxis> const m =
	{
		{ DIMOFS_X,	MouseAxis::kX },
		{ DIMOFS_Y,	MouseAxis::kY },
		{ DIMOFS_Z,	MouseAxis::kWheel },
	};

	return m.at(ofs);
}

}	// namespace detail

///////////////////////////////////////////////////////////////////////////////
//
//	メンバ関数
//
///////////////////////////////////////////////////////////////////////////////
BKSGE_INLINE
Win32MouseDevice::Win32MouseDevice(void)
	: m_device(nullptr)
	, m_granularity_z(0)
	, m_buffered(false)
	, m_hwnd(0)
	, m_coop_setting(0)
{}

BKSGE_INLINE bool
Win32MouseDevice::Initialize(
	IDirectInput8* direct_input,
	GUID	guid,
	HWND	hwnd,
	DWORD	coop_setting,
	bool	buffered)
{
	IDirectInputDevice8* mouse;
	HRESULT hr = direct_input->CreateDevice(guid, &mouse, nullptr);

	if (FAILED(hr))
	{
		// TODO	エラー処理
		return false;
	}

	hr = mouse->SetDataFormat(&c_dfDIMouse2);

	if (FAILED(hr))
	{
		// TODO	エラー処理
		return false;
	}

	if (hwnd)
	{
		hr = mouse->SetCooperativeLevel(hwnd, coop_setting);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return false;
		}
	}

	// BUFFERSIZEを設定
	//if (buffered)
	{
		DIProperty dipdw;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData	 = kBufferSize;

		hr = mouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

		if (FAILED(hr))
		{
			// TODO	エラー処理
			return false;
		}
	}

	// GRANULARITYを取得
	{
		DIProperty dipdw;
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.diph.dwObj = DIMOFS_Z;

		hr = mouse->GetProperty(DIPROP_GRANULARITY, &dipdw.diph);

		if (FAILED(hr))
		{
			// TODO エラー処理
			return false;
		}

		m_granularity_z = static_cast<int>(dipdw.dwData);
	}

	hr = mouse->Acquire();

	if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
	{
		// TODO	エラー処理
		return false;
	}

	m_device = mouse;
	m_buffered = buffered;
	m_hwnd = hwnd;
	m_coop_setting = coop_setting;

	return true;
}

BKSGE_INLINE
Win32MouseDevice::~Win32MouseDevice()
{
	if (m_device)
	{
		m_device->Unacquire();
		m_device->Release();
		m_device = nullptr;
	}
}

BKSGE_INLINE void
Win32MouseDevice::Update(void)
{
	Read();
}

BKSGE_INLINE MouseState const&
Win32MouseDevice::state(void) const
{
	return m_state;
}

BKSGE_INLINE DWORD
Win32MouseDevice::device_type(void)
{
	return DI8DEVTYPE_MOUSE;
}

BKSGE_INLINE void
Win32MouseDevice::Read(void)
{
	DIDEVICEOBJECTDATA di_buff[kBufferSize];
	DWORD entries = kBufferSize;

	HRESULT hr = m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), di_buff, &entries, 0);

	if (hr != DI_OK)
	{
		do
		{
			hr = m_device->Acquire();
		}
		while (hr == DIERR_INPUTLOST);

		hr = m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), di_buff, &entries, 0);

		//Perhaps the user just tabbed away, and coop settings
		//are nonexclusive..so just ignore
		if (FAILED(hr))
		{
			return;
		}
	}

	MouseState state;
	state.buttons() = m_state.buttons();

	for (DWORD i = 0; i < entries; ++i)
	{
		switch (di_buff[i].dwOfs)
		{
		case DIMOFS_BUTTON0:
		case DIMOFS_BUTTON1:
		case DIMOFS_BUTTON2:
		case DIMOFS_BUTTON3:
		case DIMOFS_BUTTON4:
		case DIMOFS_BUTTON5:
		case DIMOFS_BUTTON6:
		case DIMOFS_BUTTON7:
		{
			auto const button = detail::DIMOfsToMouseButton(di_buff[i].dwOfs);
			auto const data = ((di_buff[i].dwData & 0x80) != 0);
			state.pressed(button) = data;
		}
		break;

		case DIMOFS_X:
		case DIMOFS_Y:
		case DIMOFS_Z:
		{
			using SignedDataType = typename std::make_signed<DWORD>::type;
			auto const axis = detail::DIMOfsToMouseAxis(di_buff[i].dwOfs);
			auto const data = static_cast<SignedDataType>(di_buff[i].dwData);
			auto const granularity = (axis == MouseAxis::kWheel) ? m_granularity_z : 1.0f;
			state.velocity(axis) = data / granularity;
		}
		break;

		default:
			break;
		}
	}

	m_state = state;
}

}	// namespace win32

}	// namespace input

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_INPUT_WIN32_INL_WIN32_MOUSE_DEVICE_INL_HPP
