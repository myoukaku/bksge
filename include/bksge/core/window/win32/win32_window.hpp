/**
 *	@file	win32_window.hpp
 *
 *	@brief	Win32Window クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_WIN32_WIN32_WINDOW_HPP
#define BKSGE_CORE_WINDOW_WIN32_WIN32_WINDOW_HPP

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/core/window/win32/fwd/win32_window_fwd.hpp>
#include <bksge/core/window/detail/window_base.hpp>
#include <bksge/core/detail/win32.hpp>
#include <bksge/core/math/size2.hpp>
#include <string>

namespace bksge
{

namespace window
{

/**
 *	@brief
 */
class Win32Window : public WindowBase
{
private:
	using Base = WindowBase;

public:
	/**
	 *	@brief	ネイティブハンドル
	 */
	using HandleType = ::HWND;

	/**
	 *	@brief	ウィンドウを作成します
	 *
	 *	@param	client_size	ウィンドウのクライアント領域の大きさ
	 *	@param	title		ウィンドウのタイトル
	 */
	Win32Window(SizeType const& client_size, std::string const& title);

	/**
	 *	@brief	デストラクタ
	 */
	~Win32Window();

	/**
	 *	@brief	ウィンドウのプラットフォーム依存のハンドルを取得します
	 */
	HandleType handle(void) const;

private:
	void VDestroy(void) override;

	void VSetTitle(std::string const& title) override;

	void VSetClientSize(SizeType const& size) override;

	bool VUpdate(void) override;

private:
	HandleType	m_hwnd;
};

}	// namespace window

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/window/win32/inl/win32_window_inl.hpp>
#endif

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_CORE_WINDOW_WIN32_WIN32_WINDOW_HPP
