/**
 *	@file	mouse_state.hpp
 *
 *	@brief	MouseState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_MOUSE_STATE_HPP
#define BKSGE_CORE_INPUT_MOUSE_STATE_HPP

#include <bksge/core/input/mouse_button.hpp>
#include <bksge/core/input/mouse_axis.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/config.hpp>
#include <bitset>

namespace bksge
{

namespace input
{

/**
 *	@brief	マウスの入力状態を表すクラス
 */
class MouseState
{
public:
	BKSGE_STATIC_CONSTEXPR auto kButtonMax	= static_cast<bksge::size_t>(MouseButton::kMax);
	BKSGE_STATIC_CONSTEXPR auto kAxisMax	= static_cast<bksge::size_t>(MouseAxis::kMax);

	using Buttons		= std::bitset<kButtonMax>;
	using Velocities	= bksge::array<float, kAxisMax>;

	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	デフォルトコンストラクタでは以下の状態に初期化されます
	 *	・ボタンは全て押されていない
	 *	・移動量は全て0
	 */
	MouseState(void);

	/**
	 *	@brief	ボタンの押下状態を取得(const)
	 *
	 *	@param	button	取得するボタン
	 */
	bool pressed(MouseButton button) const;

	/**
	 *	@brief	ボタンの押下状態への参照を取得(非const)
	 *
	 *	@param	button	取得するボタン
	 */
	Buttons::reference pressed(MouseButton button);

	/**
	 *	@brief	移動量を取得(const)
	 *
	 *	@param	axis	取得する軸
	 */
	float velocity(MouseAxis axis) const;

	/**
	 *	@brief	移動量の参照を取得(非const)
	 *
	 *	@param	axis	取得する軸
	 */
	Velocities::reference velocity(MouseAxis axis);

	/**
	 *	@brief	ボタンの押下状態全体を取得(const)
	 */
	Buttons const& buttons(void) const;

	/**
	 *	@brief	ボタンの押下状態全体を取得(非const)
	 */
	Buttons& buttons(void);

private:
	Buttons		m_buttons;		///< マウスボタンデータ
	Velocities	m_velocities;	///< 移動量

	friend bool operator==(MouseState const& lhs, MouseState const& rhs);
};

bool operator!=(MouseState const& lhs, MouseState const& rhs);

}	// namespace input

using input::MouseState;

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/inl/mouse_state_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_MOUSE_STATE_HPP
