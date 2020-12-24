/**
 *	@file	win32_console_window_inl.hpp
 *
 *	@brief	Win32ConsoleWindow クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_WIN32_INL_WIN32_CONSOLE_WINDOW_INL_HPP
#define BKSGE_CORE_WINDOW_WIN32_INL_WIN32_CONSOLE_WINDOW_INL_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/core/window/win32/win32_console_window.hpp>
#include <bksge/core/detail/win32.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/cstdint/uint16_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace window
{

namespace detail
{

inline void OpenLastErrorMessageBox()
{
	auto error_code = ::GetLastError();
	char* buf;
	bksge::win32::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // テキストのメモリ割り当てを要求する
		FORMAT_MESSAGE_FROM_SYSTEM     | // エラーメッセージはWindowsが用意しているものを使用
		FORMAT_MESSAGE_IGNORE_INSERTS,   // 次の引数を無視してエラーコードに対するエラーメッセージを作成する
		NULL,
		error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 言語を指定
		(char*)&buf,                               // メッセージテキストが保存されるバッファへのポインタ
		0,
		NULL);

	bksge::win32::MessageBox(NULL, buf, "Error", MB_OK | MB_ICONINFORMATION);
	::LocalFree(buf);
}

inline bksge::uint16_t RGB_to_U16(bksge::uint8_t r, bksge::uint8_t g, bksge::uint8_t b)
{
	return
		(r >> 4) << 8 |
		(g >> 4) << 4 |
		(b >> 4);
}

inline bksge::uint8_t U16_to_R(bksge::uint16_t v)
{
	return ((v & 0x0F00) >> 8) << 4;
}
inline bksge::uint8_t U16_to_G(bksge::uint16_t v)
{
	return ((v & 0x00F0) >> 4) << 4;
}
inline bksge::uint8_t U16_to_B(bksge::uint16_t v)
{
	return ((v & 0x000F) >> 0) << 4;
}

inline int GetSquaredDistance(Color3<bksge::uint8_t> const& c1, Color3<bksge::uint8_t> const& c2)
{
	int result = 0;
	for (bksge::size_t i = 0; i < c1.size(); ++i)
	{
		auto x = c1[i] - c2[i];
		result += x * x;
	}
	return result;
}

struct ColorCodeInfo
{
	bksge::uint8_t	back_color;
	bksge::uint8_t	front_color;
	bksge::uint8_t	ratio;
};

template <bksge::size_t N>
inline ColorCodeInfo GetColorCodeInfo(Color3<bksge::uint8_t> const (&palette)[N], Color3<bksge::uint8_t> const& color)
{
	ColorCodeInfo result {};
	auto nearest_distance = std::numeric_limits<int>::max();

	for (bksge::size_t i = 0; i < N; ++i)
	{
		for (bksge::size_t j = 0; j < N; ++j)
		{
			for (bksge::size_t k = 0; k < 8; ++k)
			{
				auto c1 = palette[i];
				auto c2 = palette[j];
				float r = k / 8.0f;

				auto d = GetSquaredDistance(c1 * (1.0f - r) + c2 * r, color);
				if (nearest_distance > d)
				{
					nearest_distance = d;
					result.back_color  = static_cast<bksge::uint8_t>(i);
					result.front_color = static_cast<bksge::uint8_t>(j);
					result.ratio       = static_cast<bksge::uint8_t>(k);
				}
			}
		}
	}
	return result;
}

inline bksge::vector<ColorCodeInfo> ColorCodeInfoTable()
{
	static const Color3<bksge::uint8_t> palette[16] =
	{
		{   0,  0,  0 },
		{   0,  0,128 },
		{   0,128,  0 },
		{   0,128,128 },
		{ 128,  0,  0 },
		{ 128,  0,128 },
		{ 128,128,  0 },
		{ 192,192,192 },
		{ 128,128,128 },
		{   0,  0,255 },
		{   0,255,  0 },
		{   0,255,255 },
		{ 255,  0,  0 },
		{ 255,  0,255 },
		{ 255,255,  0 },
		{ 255,255,255 },
	};

	bksge::vector<ColorCodeInfo> result(0x1000);
	for (bksge::uint16_t i = 0; i < 0x1000; ++i)
	{
		auto r = U16_to_R(i);
		auto g = U16_to_G(i);
		auto b = U16_to_B(i);
		result[i] = GetColorCodeInfo(palette, Color3<bksge::uint8_t>{r, g, b});
	}
	return result;
}

inline ColorCodeInfo GetColorCodeInfo(bksge::uint8_t r, bksge::uint8_t g, bksge::uint8_t b)
{
	static auto const tbl = ColorCodeInfoTable();
	return tbl[RGB_to_U16(r, g, b)];
}

}	// namespace detail

BKSGE_INLINE
Win32ConsoleWindow::Win32ConsoleWindow(
	ExtentType const& client_size, bksge::string const& title, ExtentType const& font_size)
{
	m_console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_console == NULL)
	{
		if (!::AllocConsole())
		{
			detail::OpenLastErrorMessageBox();
		}
		m_console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	}

	BKSGE_ASSERT(m_console != INVALID_HANDLE_VALUE);

	//auto hwnd = ::GetConsoleWindow();
	//auto hdc = ::GetDC(hwnd);

	if (!::SetConsoleActiveScreenBuffer(m_console))
	{
		detail::OpenLastErrorMessageBox();
	}

	// どこにも記述がなかったのだが、フォントサイズは 2 より小さくできないっぽい。
	// スクリーンバッファサイズの計算がおかしくなるので 2 以上に制限する。
	m_font_size = {
		static_cast<short>(bksge::max(font_size.width(),  2)),
		static_cast<short>(bksge::max(font_size.height(), 2))
	};

	// ウィンドウサイズの制限に影響するので、最初にフォントサイズを設定する
	{
		::CONSOLE_FONT_INFOEX cfi{};
		cfi.cbSize     = sizeof(cfi);
		cfi.nFont      = 0;
		cfi.dwFontSize = m_font_size;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		//wcscpy_s(cfi.FaceName, L"Consolas");
		//wcscpy_s(cfi.FaceName, L"Arial");
		if (!::SetCurrentConsoleFontEx(m_console, FALSE, &cfi))
		{
			detail::OpenLastErrorMessageBox();
		}
	}

	{
		// スクリーンバッファのサイズには最小値の制限があるのでチェックする
		auto const screen_width  = bksge::max(client_size.width()  / m_font_size.X, ::GetSystemMetrics(SM_CXMIN));
		auto const screen_height = bksge::max(client_size.height() / m_font_size.Y, ::GetSystemMetrics(SM_CYMIN));
		m_screen_size = {static_cast<short>(screen_width), static_cast<short>(screen_height)};
	}

	// スクリーンバッファのサイズとウィンドウのサイズを設定するのだが、
	// スクリーンバッファサイズ > ウィンドウサイズ
	// になっていなければいけない(自動で調節してくれたりはしない)
	// そこで、設定しようとしているサイズが現在のウィンドウサイズより大きければ、
	// 　まずスクリーンバッファのサイズを設定、その後ウィンドウのサイズを設定する
	// そうでなければ、
	//　 まずウィンドウのサイズを設定、その後スクリーンバッファのサイズを設定する

	::CONSOLE_SCREEN_BUFFER_INFO csbi{};
	if (!::GetConsoleScreenBufferInfo(m_console, &csbi))
	{
		detail::OpenLastErrorMessageBox();
	}

	if (m_screen_size.X * m_screen_size.Y > csbi.srWindow.Right * csbi.srWindow.Bottom)
	{
		if (!::SetConsoleScreenBufferSize(m_console, m_screen_size))
		{
			detail::OpenLastErrorMessageBox();
		}

		// スクリーンバッファのサイズを変更するとウィンドウサイズの制限値も変わるので
		// もう一度、スクリーンバッファの情報を取得する
		if (!::GetConsoleScreenBufferInfo(m_console, &csbi))
		{
			detail::OpenLastErrorMessageBox();
		}

		auto const window_width  = bksge::min(m_screen_size.X, csbi.dwMaximumWindowSize.X);
		auto const window_height = bksge::min(m_screen_size.Y, csbi.dwMaximumWindowSize.Y);
		m_window_rect = { 0, 0, static_cast<short>(window_width-1), static_cast<short>(window_height-1) };
		if (!::SetConsoleWindowInfo(m_console, TRUE, &m_window_rect))
		{
			detail::OpenLastErrorMessageBox();
		}
	}
	else
	{
		auto const window_width  = bksge::min(m_screen_size.X, csbi.dwMaximumWindowSize.X);
		auto const window_height = bksge::min(m_screen_size.Y, csbi.dwMaximumWindowSize.Y);
		m_window_rect = { 0, 0, static_cast<short>(window_width-1), static_cast<short>(window_height-1) };
		if (!::SetConsoleWindowInfo(m_console, TRUE, &m_window_rect))
		{
			detail::OpenLastErrorMessageBox();
		}

		if (!::SetConsoleScreenBufferSize(m_console, m_screen_size))
		{
			detail::OpenLastErrorMessageBox();
		}
	}

	// カーソルを非表示にする
	{
		::CONSOLE_CURSOR_INFO cci;
		cci.dwSize   = 100;		// 1 ～ 100
		cci.bVisible = FALSE;
		if (!::SetConsoleCursorInfo(m_console, &cci))
		{
			detail::OpenLastErrorMessageBox();
		}
	}

	m_screen_buf.resize(m_screen_size.X * m_screen_size.Y);
	m_color_buf.resize(m_screen_size.X * m_screen_size.Y);

	SetTitle(title);
}

BKSGE_INLINE
Win32ConsoleWindow::~Win32ConsoleWindow()
{
	if (!::FreeConsole())
	{
		detail::OpenLastErrorMessageBox();
	}
}

BKSGE_INLINE
bool Win32ConsoleWindow::Update(void)
{
#if 1
	static const short char_code_tbl[] =
	{
		0x0000,	// 0.0 / 8.0
		0x258F,	// 1.0 / 8.0
		0x258E,	// 2.0 / 8.0
		0x258D,	// 3.0 / 8.0
		0x258C,	// 4.0 / 8.0
		0x258B,	// 5.0 / 8.0
		0x258A,	// 6.0 / 8.0
		0x2589,	// 7.0 / 8.0
	};
	bksge::size_t i = 0;
	for (auto&& c : m_color_buf)
	{
		auto info = detail::GetColorCodeInfo(c.r(), c.g(), c.b());
		m_screen_buf[i].Char.UnicodeChar = char_code_tbl[info.ratio];
		m_screen_buf[i].Attributes = (info.back_color << 4) | info.front_color;
		++i;
	}

	if (!bksge::win32::WriteConsoleOutput<wchar_t>(
			m_console, m_screen_buf.data(), m_screen_size, {0,0}, &m_window_rect))
	{
		detail::OpenLastErrorMessageBox();
	}
#else
	std::printf("\x1B[1;1H");
	for (auto&& c : m_color_buf)
	{
		std::printf("\x1B[48;2;%d;%d;%dm ", c.r(), c.g(), c.b());
	}
	std::printf("\x1B[0m");
#endif
	return true;
}

BKSGE_INLINE
void Win32ConsoleWindow::SetTitle(bksge::string const& title)
{
	if (!bksge::win32::SetConsoleTitle(title.c_str()))
	{
		detail::OpenLastErrorMessageBox();
	}
}

BKSGE_INLINE
void Win32ConsoleWindow::DrawPixel(int x, int y, Color4f const& color)
{
	x /= m_font_size.X;
	y /= m_font_size.Y;

	if (0 <= x && x < m_screen_size.X &&
		0 <= y && y < m_screen_size.Y)
	{
		auto const r = static_cast<bksge::uint8_t>(color.r() * 255);
		auto const g = static_cast<bksge::uint8_t>(color.g() * 255);
		auto const b = static_cast<bksge::uint8_t>(color.b() * 255);
		auto const color_u8 = Color3_u8(r, g, b);

		m_color_buf[y * m_screen_size.X + x] = color_u8;
	}
}

}	// namespace window

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_CORE_WINDOW_WIN32_INL_WIN32_CONSOLE_WINDOW_INL_HPP
