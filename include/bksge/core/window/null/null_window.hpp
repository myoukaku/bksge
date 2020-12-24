/**
 *	@file	null_window.hpp
 *
 *	@brief	NullWindow クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_WINDOW_NULL_NULL_WINDOW_HPP
#define BKSGE_CORE_WINDOW_NULL_NULL_WINDOW_HPP

#include <bksge/core/window/null/fwd/null_window_fwd.hpp>
#include <bksge/core/window/detail/window_base.hpp>
#include <bksge/core/math/extent2.hpp>
#include <bksge/fnd/string/string.hpp>

namespace bksge
{

namespace window
{

/**
 *	@brief
 */
class NullWindow : public WindowBase
{
private:
	using Base = WindowBase;

public:
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
	NullWindow(ExtentType const& client_size, bksge::string const& title);

	/**
	 *	@brief	デストラクタ
	 */
	~NullWindow();

	/**
	 *	@brief	ウィンドウのプラットフォーム依存のハンドルを取得します
	 */
	HandleType handle(void) const;

private:
	void VDestroy(void) override;

	void VSetTitle(bksge::string const& title) override;

	void VSetClientSize(ExtentType const& size) override;

	bool VUpdate(void) override;
};

}	// namespace window

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/window/null/inl/null_window_inl.hpp>
#endif

#endif // BKSGE_CORE_WINDOW_NULL_NULL_WINDOW_HPP
