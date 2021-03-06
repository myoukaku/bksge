﻿/**
 *	@file	sample_input_game_pad_main.cpp
 *
 *	@brief	ゲームパッド入力のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/input.hpp>
#include <iostream>

int main()
{
	bksge::GamePadManager game_pad;

	for (;;)
	{
		game_pad.Update();
		auto const& state = game_pad.state(0);

		for (bksge::size_t i = 0; i < state.kButtonMax; ++i)
		{
			std::cout << state.pressed(i);
		}
		for (bksge::size_t i = 0; i < state.kAnalogButtonMax; ++i)
		{
			std::cout << " " << state.analog_button(i);
		}
		for (bksge::size_t i = 0; i < state.kAnalogStickMax; ++i)
		{
			std::cout << " " << state.analog_stick(i);
		}
		std::cout << std::endl;
	}

	return 0;
}
