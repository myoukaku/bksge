/**
 *	@file	window.hpp
 *
 *	@brief	Window クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_WINDOW_HPP
#define BKSGE_WINDOW_WINDOW_HPP

#include <bksge/window/fwd/window_fwd.hpp>

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)
#	include <bksge/window/win32/win32_window.hpp>
#else
#	include <bksge/window/null/null_window.hpp>
#endif

#endif // BKSGE_WINDOW_WINDOW_HPP
