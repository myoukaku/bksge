/**
 *	@file	mouse_button.hpp
 *
 *	@brief	MouseButton の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_MOUSE_BUTTON_HPP
#define BKSGE_INPUT_MOUSE_BUTTON_HPP

namespace bksge
{

namespace input
{

/**
 *	@brief	マウスのボタンの定義
 */
enum class MouseButton
{
	k0,
	k1,
	k2,
	k3,
	k4,
	k5,
	k6,
	k7,

	kMax,	// 総数

	// 以下はエイリアス
	kLeft	= k0,
	kRight	= k1,
	kMiddle	= k2,
};

}	// namespace input

using input::MouseButton;

}	// namespace bksge

#endif // BKSGE_INPUT_MOUSE_BUTTON_HPP
