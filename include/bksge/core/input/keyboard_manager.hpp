/**
 *	@file	keyboard_manager.hpp
 *
 *	@brief	KeyboardManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_KEYBOARD_MANAGER_HPP
#define BKSGE_CORE_INPUT_KEYBOARD_MANAGER_HPP

#include <bksge/core/input/config.hpp>

#if defined(BKSGE_CORE_INPUT_KEYBOARD_MANAGER_HEADER)
#	include BKSGE_CORE_INPUT_KEYBOARD_MANAGER_HEADER
#else
#	if defined(BKSGE_PLATFORM_WIN32)
#		include	<bksge/core/input/win32/win32_keyboard_manager.hpp>
#	else
#		include	<bksge/core/input/null/null_keyboard_manager.hpp>
#	endif
#endif

namespace bksge
{

using input::KeyboardManager;

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_KEYBOARD_MANAGER_HPP
