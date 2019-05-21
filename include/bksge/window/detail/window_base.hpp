/**
 *	@file	window_base.hpp
 *
 *	@brief	WindowBase クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_WINDOW_DETAIL_WINDOW_BASE_HPP
#define BKSGE_WINDOW_DETAIL_WINDOW_BASE_HPP

#include <bksge/math/size2.hpp>
#include <bksge/config.hpp>
#include <cstdint>
#include <string>

namespace bksge
{

namespace window
{

/**
 *	@brief
 */
class WindowBase
{
public:
	/**
	 *	@brief	幅と高さを表す型
	 */
	using SizeType = Size2<std::int32_t>;

	/**
	 *	@brief	ウィンドウを作成します
	 *
	 *	@param	client_size	ウィンドウのクライアント領域の大きさ
	 *	@param	title		ウィンドウのタイトル
	 */
	WindowBase(SizeType const& client_size, std::string const& title);

	/**
	 *	@brief	デストラクタ
	 */
	virtual ~WindowBase();

	/**
	 *	@brief	ウィンドウを破棄します
	 */
	void Destroy(void);

	/**
	 *	@brief	ウィンドウメッセージを処理します
	 *
	 *	@return	ウィンドウが閉じられたときにfalseを返します。
	 */
	bool Update(void);

	/**
	 *	@brief	ウィンドウタイトルを設定します
	 */
	void SetTitle(std::string const& title);

	/**
	 *	@brief	ウィンドウのクライアント領域のサイズを設定します
	 */
	void SetClientSize(SizeType const& size);

	/**
	 *	@brief	ウィンドウタイトルを取得します
	 */
	std::string const& title(void) const;

	/**
	 *	@brief	ウィンドウのクライアント領域のサイズを取得します
	 */
	SizeType client_size(void) const;

private:
	virtual void VDestroy(void) = 0;

	virtual bool VUpdate(void) = 0;

	virtual void VSetTitle(std::string const& title) = 0;

	virtual void VSetClientSize(SizeType const& size) = 0;

private:
	SizeType		m_client_size;
	std::string		m_title;
};

}	// namespace window

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/window/detail/inl/window_base_inl.hpp>
#endif

#endif // BKSGE_WINDOW_DETAIL_WINDOW_BASE_HPP
