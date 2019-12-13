/**
 *	@file	window.hpp
 *
 *	@brief	Window クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_WINDOW_HPP
#define BKSGE_CORE_WINDOW_WINDOW_HPP

#include <bksge/core/window/fwd/window_fwd.hpp>

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)
#	include <bksge/core/window/win32/win32_window.hpp>
#else
#	include <bksge/core/window/null/null_window.hpp>
#endif

#endif // BKSGE_CORE_WINDOW_WINDOW_HPP
