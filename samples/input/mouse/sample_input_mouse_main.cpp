/**
 *	@file	sample_input_mouse_main.cpp
 *
 *	@brief	マウス入力のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/input.hpp>
#include <bksge/math.hpp>
#include <iostream>

int main()
{
	bksge::MouseManager mouse;

	for (;;)
	{
		mouse.Update();
		auto const& state = mouse.state(0);

		if (state.pressed(bksge::MouseButton::kLeft))
		{
			std::cout << "Press: Left" << std::endl;
		}
		if (state.pressed(bksge::MouseButton::kRight))
		{
			std::cout << "Press: Right" << std::endl;
		}
		if (state.pressed(bksge::MouseButton::kMiddle))
		{
			std::cout << "Press: Middle" << std::endl;
		}

		bksge::Vector3f const vel(
			state.velocity(bksge::MouseAxis::kX),
			state.velocity(bksge::MouseAxis::kY),
			state.velocity(bksge::MouseAxis::kWheel));

		if (vel != bksge::Vector3f::Zero())
		{
			std::cout << vel << std::endl;
		}
	}

	return 0;
}
