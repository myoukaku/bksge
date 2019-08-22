/**
 *	@file	win32_input_manager_impl_inl.hpp
 *
 *	@brief	Win32InputManagerImpl の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_INL_WIN32_INPUT_MANAGER_IMPL_INL_HPP
#define BKSGE_INPUT_WIN32_INL_WIN32_INPUT_MANAGER_IMPL_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/input/win32/win32_input_manager_impl.hpp>
#include <bksge/input/win32/win32_direct_input.hpp>
#include <cstddef>
#include <memory>

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

template <typename Device> inline
Win32InputManagerImpl<Device>::Win32InputManagerImpl(void)
{
	auto direct_input = Win32DirectInput::get();

	CallbackParam param;
	param.direct_input = direct_input;
	param.hwnd         = nullptr;
	param.coop_setting = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	param.buffered     = false;
	param.device_list  = &m_device_list;

	direct_input->EnumDevices(
		Device::device_type(),
		EnumDevicesCallback,
		&param,
		DIEDFL_ALLDEVICES);
}

template <typename Device> inline
Win32InputManagerImpl<Device>::~Win32InputManagerImpl()
{}

template <typename Device> inline
void Win32InputManagerImpl<Device>::Update(void)
{
	for (auto& device : m_device_list)
	{
		device->Update();
	}
}

template <typename Device> inline
auto Win32InputManagerImpl<Device>::GetState(std::size_t index) const
-> State const&
{
	if (index >= m_device_list.size())
	{
		static State dummy_state;
		return dummy_state;
	}

	return m_device_list[index]->state();
}

template <typename Device>
inline BOOL CALLBACK
Win32InputManagerImpl<Device>::EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	auto param = reinterpret_cast<CallbackParam*>(pvRef);
	auto device = std::make_shared<Device>();
	auto const success = device->Initialize(
		param->direct_input,
		lpddi->guidInstance,
		param->hwnd,
		param->coop_setting,
		param->buffered);

	if (!success)
	{
		return DIENUM_STOP;
	}

	param->device_list->push_back(device);
	return DIENUM_CONTINUE;
}

}	// namespace win32

}	// namespace input

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_INPUT_WIN32_INL_WIN32_INPUT_MANAGER_IMPL_INL_HPP
