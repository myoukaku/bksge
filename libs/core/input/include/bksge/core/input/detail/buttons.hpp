/**
 *	@file	buttons.hpp
 *
 *	@brief	Buttons クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_DETAIL_BUTTONS_HPP
#define BKSGE_CORE_INPUT_DETAIL_BUTTONS_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/bitset.hpp>

namespace bksge
{

namespace input
{

namespace detail
{

/**
 *	@brief	ボタン入力のOn,Off,Repeatを処理するクラステンプレート
 */
template <bksge::size_t N>
class Buttons
{
public:
	/**
	 *	@brief	指定のボタンが押されているか取得
	 *
	 *	@param	index	ボタン番号(0 <= index < N)
	 *
	 *	@return	押されていたらtrue
	 */
	bool IsPressed(bksge::size_t index) const
	{
		return m_press[index];
	}

	/**
	 *	@brief	指定のボタンが新たに押されたか取得
	 *
	 *	@param	index	ボタン番号(0 <= index < N)
	 *
	 *	@return	新たに押されていたらtrue
	 */
	bool IsTriggered(bksge::size_t index) const
	{
		return m_trigger[index];
	}

	/**
	 *	@brief	指定のボタンが新たに離されたか取得
	 *
	 *	@param	index	ボタン番号(0 <= index < N)
	 *
	 *	@return	離されていたらtrue
	 */
	bool IsReleased(bksge::size_t index) const
	{
		return m_release[index];
	}

	/**
	 *	@brief	指定のボタンの押下状態を設定
	 *
	 *	@param	index	ボタン番号(0 <= index < N)
	 *	@param	pressed	trueなら押されている
	 */
	void SetPressed(bksge::size_t index, bool pressed)
	{
		m_press[index] = pressed;
	}

	/**
	 *	@brief	ボタン押下状態をリセット
	 *
	 *	@note	ボタンが全て離された状態になります
	 */
	void ResetPressed(void)
	{
		m_press.reset();
	}

	/**
	 *	@brief	Updateの最初に呼ぶ
	 */
	void BeginUpdate(void)
	{
		m_press_old = m_press;
	}

	/**
	 *	@brief	Updateの最後に呼ぶ
	 */
	void EndUpdate(void)
	{
		m_trigger = (m_press_old ^ m_press) & m_press;
		m_release = (m_press_old ^ m_press) & m_press_old;
	}

private:
	using ValueType = bksge::bitset<N>;

	ValueType			m_press;
	ValueType			m_press_old;
	ValueType			m_trigger;
	ValueType			m_release;
};

}	// namespace detail

}	// namespace input

}	// namespace bksge

#endif // BKSGE_CORE_INPUT_DETAIL_BUTTONS_HPP
