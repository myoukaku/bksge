/**
 *	@file	mouse_manager.hpp
 *
 *	@brief	MouseManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_MOUSE_MANAGER_HPP
#define BKSGE_INPUT_MOUSE_MANAGER_HPP

#include <bksge/input/config.hpp>

#if defined(BKSGE_INPUT_MOUSE_MANAGER_HEADER)
#	include BKSGE_INPUT_MOUSE_MANAGER_HEADER
#else
#	if defined(BKSGE_PLATFORM_WIN32)
#		include	<bksge/input/win32/win32_mouse_manager.hpp>
#	else
#		include	<bksge/input/dummy/dummy_mouse_manager.hpp>
#	endif
#endif

namespace bksge
{

using input::MouseManager;

}	// namespace bksge

#endif // BKSGE_INPUT_MOUSE_MANAGER_HPP
