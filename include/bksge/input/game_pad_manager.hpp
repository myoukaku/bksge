/**
 *	@file	game_pad_manager.hpp
 *
 *	@brief	GamePadManager の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_GAME_PAD_MANAGER_HPP
#define BKSGE_INPUT_GAME_PAD_MANAGER_HPP

#include <bksge/input/config.hpp>

#if defined(BKSGE_INPUT_GAME_PAD_MANAGER_HEADER)
#	include BKSGE_INPUT_GAME_PAD_MANAGER_HEADER
#else
#	if defined(BKSGE_PLATFORM_WIN32)
#		include	<bksge/input/win32/win32_game_pad_manager.hpp>
#	else
#		include	<bksge/input/null/null_game_pad_manager.hpp>
#	endif
#endif

namespace bksge
{

using input::GamePadManager;

}	// namespace bksge

#endif // BKSGE_INPUT_GAME_PAD_MANAGER_HPP
