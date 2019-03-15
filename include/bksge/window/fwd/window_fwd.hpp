/**
 *	@file	window_fwd.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_FWD_WINDOW_FWD_HPP
#define BKSGE_WINDOW_FWD_WINDOW_FWD_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)
#	include <bksge/window/win32/fwd/win32_window_fwd.hpp>
#	define BKSGE_WINDOW_WINDOW Win32Window
#else
#	include <bksge/window/dummy/fwd/dummy_window_fwd.hpp>
#	define BKSGE_WINDOW_WINDOW DummyWindow
#endif

namespace bksge
{

namespace window
{

using Window = BKSGE_WINDOW_WINDOW;

}	// namespace window

using window::Window;

}	// namespace bksge

#endif // BKSGE_WINDOW_FWD_WINDOW_FWD_HPP
