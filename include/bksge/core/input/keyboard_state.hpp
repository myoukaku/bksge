/**
 *	@file	keyboard_state.hpp
 *
 *	@brief	KeyboardState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_INPUT_KEYBOARD_STATE_HPP
#define BKSGE_CORE_INPUT_KEYBOARD_STATE_HPP

#include <bksge/core/input/key_code.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <bitset>

namespace bksge
{

namespace input
{

/**
 *	@brief	キーボードの入力状態を表すクラス
 */
class KeyboardState
{
public:
	BKSGE_STATIC_CONSTEXPR auto kKeyCodeMax	=
		static_cast<bksge::size_t>(KeyCode::kMax);

	using Keys = std::bitset<kKeyCodeMax>;

	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	デフォルトコンストラクタでは以下の状態に初期化されます
	 *	・キーは全て押されていない
	 */
	KeyboardState(void);

	/**
	 *	@brief	キーの押下状態を取得(const)
	 *
	 *	@param	button	取得するキー
	 */
	bool pressed(KeyCode key_code) const;

	/**
	 *	@brief	キーの押下状態への参照を取得(非const)
	 *
	 *	@param	button	取得するキー
	 */
	Keys::reference pressed(KeyCode key_code);

private:
	Keys		m_keys;		///< キーデータ

	friend bool operator==(KeyboardState const& lhs, KeyboardState const& rhs);
};

bool operator!=(KeyboardState const& lhs, KeyboardState const& rhs);

}	// namespace input

using input::KeyboardState;

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/input/inl/keyboard_state_inl.hpp>
#endif

#endif // BKSGE_CORE_INPUT_KEYBOARD_STATE_HPP
