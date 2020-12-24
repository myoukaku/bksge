/**
 *	@file	sample_window_console_window_main.cpp
 *
 *	@brief	ConsoleWindow のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/window/win32/win32_console_window.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <iomanip>
#include <chrono>

int main()
{
#if defined(BKSGE_PLATFORM_WIN32)
	using ConsoleWindow = bksge::window::Win32ConsoleWindow;

	int scale = 1;
	int width  = 640 * scale;
	int height = 360 * scale;
	ConsoleWindow window({width, height}, "", {4 * scale, 8 * scale});

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float r = (float)x / width;
			float g = (float)y / height;
			float b = 1;
			window.DrawPixel(x, y, bksge::Color4f(r,g,b,1));
		}
	}

	auto current_time = std::chrono::high_resolution_clock::now();
	while (window.Update())
	{
		auto t = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(t - current_time);
		current_time = t;

		bksge::stringstream ss;
		ss << "console_window: " << std::fixed << std::setprecision(2)
			<< std::chrono::duration<float>(1) / elapsed_time << " fps";
		window.SetTitle(ss.str());
	}
#endif
	return 0;
}
