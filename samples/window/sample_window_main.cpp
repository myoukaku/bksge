/**
 *	@file	sample_window_main.cpp
 *
 *	@brief	Window のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>

int main()
{
	bksge::Window window({800, 600}, "sample_window");

	while (window.Update())
	{
	}

	return 0;
}
