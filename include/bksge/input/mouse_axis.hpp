/**
 *	@file	mouse_axis.hpp
 *
 *	@brief	MouseAxis の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_INPUT_MOUSE_AXIS_HPP
#define BKSGE_INPUT_MOUSE_AXIS_HPP

namespace bksge
{

namespace input
{

/**
 *	@brief	マウスの移動量の軸の定義
 */
enum class MouseAxis
{
	kX,			///< X方向
	kY,			///< Y方向
	kWheel,		///< ホイール
	kTilt,		///< チルト

	kMax,		// 総数
};

}	// namespace input

using input::MouseAxis;

}	// namespace bksge

#endif // BKSGE_INPUT_MOUSE_AXIS_HPP
