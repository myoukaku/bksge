/**
 *	@file	diproperty.hpp
 *
 *	@brief	DIProperty の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_WIN32_DIPROPERTY_HPP
#define BKSGE_INPUT_WIN32_DIPROPERTY_HPP

#include <bksge/input/win32/dinput.hpp>

namespace bksge
{

namespace input
{

/**
 *	@brief	DIPROPDWORDのラッパー
 */
struct DIProperty : public DIPROPDWORD
{
	DIProperty(void)
	{
		diph.dwSize			= sizeof(DIPROPDWORD);
		diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		diph.dwObj			= 0;
		diph.dwHow			= DIPH_DEVICE;
		dwData				= 0;
	}
};

/**
 *	@brief	DIPROPRANGEのラッパー
 */
struct DIPropertyRange : public DIPROPRANGE
{
	DIPropertyRange(void)
	{
		diph.dwSize	        = sizeof(DIPROPRANGE);
		diph.dwHeaderSize	= sizeof(DIPROPHEADER);
		diph.dwObj	        = 0;
		diph.dwHow	        = DIPH_DEVICE;
		lMin	            = 0;
		lMax	            = 0;
	}
};

}	// namespace input

}	// namespace bksge

#endif // BKSGE_INPUT_WIN32_DIPROPERTY_HPP
