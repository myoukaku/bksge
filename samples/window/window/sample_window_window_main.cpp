/**
 *	@file	sample_window_window_main.cpp
 *
 *	@brief	Window のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <sstream>

int WINAPI WinMain(
	HINSTANCE /*hInstance*/, 
	HINSTANCE /*hPrevInstance*/, 
	LPSTR /*lpCmdLine*/, 
	int /*nCmdShow*/)
{
	bksge::Window window({800, 600}, "sample_window");

	int count = 0;
	while (window.Update())
	{
		std::stringstream ss;
		ss << "sample_window: " << count;
		window.SetTitle(ss.str());
		++count;
	}

	return 0;
}
