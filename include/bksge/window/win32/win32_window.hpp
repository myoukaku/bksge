/**
 *	@file	win32_window.hpp
 *
 *	@brief	Win32Window クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_WIN32_WIN32_WINDOW_HPP
#define BKSGE_WINDOW_WIN32_WIN32_WINDOW_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/window/win32/fwd/win32_window_fwd.hpp>
#include <bksge/detail/win32.hpp>
#include <bksge/math/size2.hpp>
#include <cstdint>
#include <string>

namespace bksge
{

namespace window
{

/**
 *	@brief
 */
class Win32Window
{
public:
	/**
	 *	@brief	幅と高さを表す型
	 */
	using SizeType = Size2<std::int32_t>;

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
	 *	@brief	ウィンドウを破棄します
	 */
	void Destroy(void);

	/**
	 *	@brief	ウィンドウタイトルを設定します
	 */
	void SetTitle(std::string const& title);

	/**
	 *	@brief	ウィンドウのクライアント領域のサイズを設定します
	 */
	void SetClientSize(SizeType const& size);

	/**
	 *	@brief	ウィンドウのクライアント領域のサイズを取得します
	 */
	SizeType ClientSize(void) const;

	/**
	 *	@brief	ウィンドウメッセージを処理します
	 *
	 *	@return	ウィンドウが閉じられたときにfalseを返します。
	 */
	bool Update(void);

	/**
	 *	@brief	ウィンドウのプラットフォーム依存のハンドルを取得します
	 */
	HandleType Handle(void) const;

private:
	HandleType	m_hwnd;
};

}	// namespace window

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/window/win32/inl/win32_window_inl.hpp>
#endif

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_WINDOW_WIN32_WIN32_WINDOW_HPP
