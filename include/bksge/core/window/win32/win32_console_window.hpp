/**
 *	@file	win32_console_window.hpp
 *
 *	@brief	Win32ConsoleWindow クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_WIN32_WIN32_CONSOLE_WINDOW_HPP
#define BKSGE_CORE_WINDOW_WIN32_WIN32_CONSOLE_WINDOW_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/core/detail/win32.hpp>
#include <bksge/core/math/extent2.hpp>
#include <bksge/core/math/color4.hpp>
#include <bksge/core/math/color3.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/cstdint/int32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <vector>

namespace bksge
{

namespace window
{

class Win32ConsoleWindow
{
public:
	using ExtentType = Extent2<bksge::int32_t>;

	Win32ConsoleWindow(
		ExtentType const& client_size,
		bksge::string const& title,
		ExtentType const& font_size);

	~Win32ConsoleWindow();

	bool Update(void);

	void SetTitle(bksge::string const& title);

	void DrawPixel(int x, int y, Color4f const& color);

private:
	using Color3_u8 = Color3<bksge::uint8_t>;
	::HANDLE					m_console;
	::COORD						m_font_size;
	::COORD						m_screen_size;
	::SMALL_RECT				m_window_rect;
	std::vector<::CHAR_INFO>	m_screen_buf;
	std::vector<Color3_u8>		m_color_buf;
};

}	// namespace window

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/window/win32/inl/win32_console_window_inl.hpp>
#endif

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_CORE_WINDOW_WIN32_WIN32_CONSOLE_WINDOW_HPP
