/**
 *	@file	win32_window_inl.hpp
 *
 *	@brief	Win32Window クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_WIN32_INL_WIN32_WINDOW_INL_HPP
#define BKSGE_WINDOW_WIN32_INL_WIN32_WINDOW_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/window/win32/win32_window.hpp>
#include <string>

namespace bksge
{

namespace window
{

namespace win32_window_detail
{

inline int GetUniqueNumber(void)
{
	static int s_count = 0;
	return s_count++;
}

template <typename CharT>
std::basic_string<CharT> GetUniqueClassName(void);

template <> inline
std::basic_string<char> GetUniqueClassName(void)
{
	return "BksgeWindow" + std::to_string(GetUniqueNumber());
}

template <> inline
std::basic_string<wchar_t> GetUniqueClassName(void)
{
	return L"BksgeWindow" + std::to_wstring(GetUniqueNumber());
}

template <typename CharT> inline
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	if (msg == WM_CREATE)
	{
		// Win32Windowクラスへのポインタをセットします。
		// これはCreateWindowExの引数で渡されたものです。
		auto const* create_struct = reinterpret_cast<LPCREATESTRUCT>(l_param);
		win32::SetWindowLongPtr<CharT>(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(create_struct->lpCreateParams));

		return 0;
	}

	// Win32Windowクラスへのポインタを取得します。
	// WM_CREATEより前に別のメッセージが来ることがあり、その場合nullptrになることに注意
	auto* this_ = reinterpret_cast<Win32Window*>(win32::GetWindowLongPtr<CharT>(hwnd, GWLP_USERDATA));

	if (!this_)
	{
		return win32::DefWindowProc<CharT>(hwnd, msg, w_param, l_param);
	}

	switch (msg)
	{
	case WM_CLOSE:
		this_->Destroy();
		return 0;

	case WM_DESTROY:
		win32::PostQuitMessage(0);
		break;
	}

	return win32::DefWindowProc<CharT>(hwnd, msg, w_param, l_param);
}

template <typename CharT> inline
bool RegisterWindowClass(std::basic_string<CharT> const& class_name)
{
	auto const instance = win32::GetModuleHandle<CharT>(nullptr);
	using WC = typename win32::WindowClassEx<CharT>::type;
	WC const wc =
	{
		sizeof(WC),
		CS_OWNDC,
		WndProc<CharT>,
		0,
		0,
		instance,
		win32::LoadIcon(nullptr, IDI_APPLICATION),
		win32::LoadCursor(nullptr, IDC_ARROW),
		win32::CreateSolidBrush(RGB(0, 0, 0)),
		nullptr,
		class_name.c_str(),
		nullptr
	};

	if (win32::RegisterClassEx(&wc) == 0)
	{
		return false;
	}

	return true;
}

inline int Width(::RECT const& r)
{
	return r.right - r.left;
}

inline int Height(::RECT const& r)
{
	return r.bottom - r.top;
}

// クライアントサイズからウィンドウサイズを計算します
inline Win32Window::SizeType CalcWindowSize(
	Win32Window::SizeType const& client_size,
	DWORD window_style,
	bool has_menu,
	DWORD window_style_ex)
{
	auto const width  = client_size.width();
	auto const height = client_size.height();
	::RECT r;
	::SetRect(&r, 0, 0, width, height);
	::AdjustWindowRectEx(&r, window_style, has_menu, window_style_ex);

	return Win32Window::SizeType{ Width(r), Height(r) };
}

template <typename CharT> inline
HWND Create(Win32Window::SizeType const& client_size, CharT const* title, Win32Window* this_)
{
	auto const class_name = GetUniqueClassName<CharT>();

	if (!RegisterWindowClass(class_name))
	{
		return nullptr;
	}

	DWORD const window_style_ex = WS_EX_OVERLAPPEDWINDOW;
	DWORD const window_style = WS_OVERLAPPEDWINDOW;
	bool  const has_menu = false;
	auto  const window_size = CalcWindowSize(client_size, window_style, has_menu, window_style_ex);

	return win32::CreateWindowEx(
			   window_style_ex,
			   class_name.c_str(),
			   title,
			   window_style,
			   0,	// x
			   0,	// y
			   window_size.width(),
			   window_size.height(),
			   0,	// parent
			   0,	// menu
			   win32::GetModuleHandle<CharT>(nullptr),
			   this_);
}

inline void SetClientSize(HWND hwnd, Win32Window::SizeType const& size)
{
	::RECT window_rect;
	::GetWindowRect(hwnd, &window_rect);

	::RECT client_rect;
	::GetClientRect(hwnd, &client_rect);

	auto const width  = size.width();
	auto const height = size.height();
	auto const new_width  = Width(window_rect)  - Width(client_rect)  + width;
	auto const new_height = Height(window_rect) - Height(client_rect) + height;

	win32::SetWindowPos(hwnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);
}

}	// namespace win32_window_detail

BKSGE_INLINE
Win32Window::Win32Window(SizeType const& client_size, std::string const& title)
	: Base(client_size, title)
	, m_hwnd(nullptr)
{
	m_hwnd = win32_window_detail::Create(client_size, title.c_str(), this);
	win32::ShowWindow(m_hwnd, SW_SHOW);
}

BKSGE_INLINE
Win32Window::~Win32Window()
{
	Destroy();
}

BKSGE_INLINE void
Win32Window::VDestroy(void)
{
	if (m_hwnd)
	{
		win32::DestroyWindow(m_hwnd);
	}

	m_hwnd = nullptr;
}

BKSGE_INLINE void
Win32Window::VSetTitle(std::string const& title)
{
	win32::SetWindowText(m_hwnd, title.c_str());
}

BKSGE_INLINE void
Win32Window::VSetClientSize(SizeType const& size)
{
	win32_window_detail::SetClientSize(m_hwnd, size);
}

BKSGE_INLINE bool
Win32Window::VUpdate(void)
{
	::MSG msg;

	while (win32::PeekMessage(&msg, m_hwnd, 0U, 0U, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		//if (!win32::TranslateAccelerator(m_hwnd, haccel, &msg))
		{
			win32::TranslateMessage(&msg);
			win32::DispatchMessage(&msg);
		}
	}

	return true;
}

BKSGE_INLINE auto
Win32Window::handle(void) const
-> HandleType
{
	return m_hwnd;
}

}	// namespace window

}	// namespace bksge

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_WINDOW_WIN32_INL_WIN32_WINDOW_INL_HPP
