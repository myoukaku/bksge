﻿/**
 *	@file	win32_input_manager_impl.hpp
 *
 *	@brief	Win32InputManagerImpl の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_WIN32_INPUT_MANAGER_IMPL_HPP
#define BKSGE_INPUT_WIN32_WIN32_INPUT_MANAGER_IMPL_HPP

#include <bksge/input/win32/dinput.hpp>
#include <cstddef>
#include <memory>
#include <vector>

namespace bksge
{

namespace input
{

namespace win32
{

/**
 *	@brief	Win32のInputManagerの基底となるクラステンプレート
 */
template <typename Device>
class Win32InputManagerImpl
{
public:
	using State = typename Device::State;

	Win32InputManagerImpl(void);

	~Win32InputManagerImpl();

	void Update(void);

	State const& GetState(std::size_t index) const;

private:
	static BOOL CALLBACK EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

	using DeviceList = std::vector<std::shared_ptr<Device>>;

	struct CallbackParam
	{
		IDirectInput8*	direct_input;
		HWND			hwnd;
		DWORD			coop_setting;
		bool			buffered;
		DeviceList*		device_list;
	};

	DeviceList	m_device_list;
};

}	// namespace win32

}	// namespace input

}	// namespace bksge

#include <bksge/input/win32/inl/win32_input_manager_impl_inl.hpp>

#endif // BKSGE_INPUT_WIN32_WIN32_INPUT_MANAGER_IMPL_HPP
