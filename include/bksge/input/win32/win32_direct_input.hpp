/**
 *	@file	win32_direct_input.hpp
 *
 *	@brief	Win32DirectInput の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_WIN32_DIRECT_INPUT_HPP
#define BKSGE_INPUT_WIN32_WIN32_DIRECT_INPUT_HPP

#include <bksge/input/win32/dinput.hpp>

namespace bksge
{

namespace input
{

namespace win32
{

/**
 *	@brief	DirectInputの唯一のインスタンスを得るためのクラス
 */
class Win32DirectInput
{
public:
	static IDirectInput8* get(void);

private:
	Win32DirectInput(void);

	~Win32DirectInput();

	IDirectInput8*	m_direct_input;
};

}	// namespace win32

}	// namespace input

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/input/win32/inl/win32_direct_input_inl.hpp>
#endif

#endif // BKSGE_INPUT_WIN32_WIN32_DIRECT_INPUT_HPP
