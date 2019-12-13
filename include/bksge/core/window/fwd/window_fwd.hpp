/**
 *	@file	window_fwd.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_FWD_WINDOW_FWD_HPP
#define BKSGE_CORE_WINDOW_FWD_WINDOW_FWD_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)
#	include <bksge/core/window/win32/fwd/win32_window_fwd.hpp>
#	define BKSGE_CORE_WINDOW_WINDOW Win32Window
#else
#	include <bksge/core/window/null/fwd/null_window_fwd.hpp>
#	define BKSGE_CORE_WINDOW_WINDOW NullWindow
#endif

namespace bksge
{

namespace window
{

using Window = BKSGE_CORE_WINDOW_WINDOW;

}	// namespace window

using window::Window;

}	// namespace bksge

#endif // BKSGE_CORE_WINDOW_FWD_WINDOW_FWD_HPP
