/**
 *	@file	game_pad_state.hpp
 *
 *	@brief	GamePadState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_GAME_PAD_STATE_HPP
#define BKSGE_CORE_INPUT_GAME_PAD_STATE_HPP

#include <bksge/core/math/vector2.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/config.hpp>
#include <bitset>
#include <cstddef>

namespace bksge
{

namespace input
{

/**
 *	@brief	ゲームパッドの入力状態を表すクラス
 */
class GamePadState
{
public:
	BKSGE_STATIC_CONSTEXPR std::size_t kButtonMax		= 32;
	BKSGE_STATIC_CONSTEXPR std::size_t kAnalogButtonMax	=  2;
	BKSGE_STATIC_CONSTEXPR std::size_t kAnalogStickMax	=  2;

	using Buttons		= std::bitset<kButtonMax>;
	using AnalogButtons	= bksge::array<float, kAnalogButtonMax>;
	using AnalogSticks	= bksge::array<bksge::Vector2f, kAnalogStickMax>;

	GamePadState(void);

	/**
	 *	@brief	ボタンの押下状態を取得(const)
	 *
	 *	@param	button	取得するボタン
	 */
	bool pressed(std::size_t button) const;

	/**
	 *	@brief	ボタンの押下状態への参照を取得(非const)
	 *
	 *	@param	button	取得するボタン
	 */
	Buttons::reference pressed(std::size_t button);

	/**
	 *	@brief	アナログボタンの押下状態を取得(const)
	 *
	 *	@param	button	取得するボタン
	 */
	AnalogButtons::const_reference analog_button(std::size_t button) const;

	/**
	 *	@brief	アナログボタンの押下状態への参照を取得(非const)
	 *
	 *	@param	button	取得するボタン
	 */
	AnalogButtons::reference analog_button(std::size_t button);

	/**
	 *	@brief	アナログスティックの値を取得(const)
	 *
	 *	@param	button	取得するボタン
	 */
	AnalogSticks::const_reference analog_stick(std::size_t stick) const;

	/**
	 *	@brief	アナログスティックの値への参照を取得(非const)
	 *
	 *	@param	button	取得するボタン
	 */
	AnalogSticks::reference analog_stick(std::size_t stick);

private:
	Buttons				m_buttons;			///< デジタルボタンデータ
	AnalogButtons		m_analog_buttons;	///< アナログボタンデータ
	AnalogSticks		m_analog_sticks;	///< アナログスティックデータ
//	Quaternionf			m_orientation;		///< コントローラの姿勢値
//	Vector3f			m_acceleration;		///< 加速度センサーの値
//	Vector3f			m_angular_velocity;	///< 角速度センサーの値
//	GamePadTouchData	m_touch_data;		///< タッチパッドのデータ

	friend bool operator==(GamePadState const& lhs, GamePadState const& rhs);
};

bool operator!=(GamePadState const& lhs, GamePadState const& rhs);

}	// namespace input

using input::GamePadState;

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/inl/game_pad_state_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_GAME_PAD_STATE_HPP
