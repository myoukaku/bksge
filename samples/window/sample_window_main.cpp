/**
 *	@file	sample_window_main.cpp
 *
 *	@brief	Window のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <sstream>

int main()
{
	bksge::Window window({800, 600}, "sample_window");

	int count = 0;
	while (window.Update())
	{
		//std::stringstream ss;
		//ss << "sample_window: " << count;
		//window.SetTitle(ss.str());
		++count;
	}

	return 0;
}
