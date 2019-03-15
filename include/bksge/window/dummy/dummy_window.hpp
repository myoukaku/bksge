/**
 *	@file	dummy_window.hpp
 *
 *	@brief	DummyWindow クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_DUMMY_DUMMY_WINDOW_HPP
#define BKSGE_WINDOW_DUMMY_DUMMY_WINDOW_HPP

#include <bksge/window/dummy/fwd/dummy_window_fwd.hpp>
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
class DummyWindow
{
public:
	/**
	 *	@brief	幅と高さを表す型
	 */
	using SizeType = Size2<std::int32_t>;

	/**
	 *	@brief	ネイティブハンドル
	 */
	class HandleType{};

	/**
	 *	@brief	ウィンドウを作成します
	 *
	 *	@param	client_size	ウィンドウのクライアント領域の大きさ
	 *	@param	title		ウィンドウのタイトル
	 */
	DummyWindow(SizeType const& client_size, std::string const& title);

	/**
	 *	@brief	デストラクタ
	 */
	~DummyWindow();

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
};

}	// namespace window

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/window/dummy/inl/dummy_window_inl.hpp>
#endif

#endif // BKSGE_WINDOW_DUMMY_DUMMY_WINDOW_HPP
