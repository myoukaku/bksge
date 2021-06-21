/**
 *	@file	sample_input_keyboard_main.cpp
 *
 *	@brief	キーボード入力のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/input.hpp>
#include <iostream>

int main()
{
	bksge::KeyboardManager keyboard;

	for (;;)
	{
		keyboard.Update();
		auto const& state = keyboard.state(0);

		if (state.pressed(bksge::KeyCode::kA))
		{
			std::cout << "Press: A" << std::endl;
		}
		if (state.pressed(bksge::KeyCode::kB))
		{
			std::cout << "Press: B" << std::endl;
		}
		if (state.pressed(bksge::KeyCode::kQ))
		{
			break;
		}
	}

	return 0;
}
