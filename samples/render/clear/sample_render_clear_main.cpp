/**
 *	@file	sample_render_clear_main.cpp
 *
 *	@brief	レンダーターゲットをクリアするサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/window.hpp>
#include <bksge/render.hpp>

int main()
{
	bksge::Window window({800, 600}, "sample_render_clear");

#if 1
	bksge::GlRenderer renderer;
#elif 1
	bksge::D3D12Renderer renderer;
#else
	bksge::D3D11Renderer renderer;
#endif
	renderer.SetRenderTarget(window);

	float r = 0;
	float g = 0;
	float b = 0;

	while (window.Update())
	{
		renderer.SetClearColor({r, g, b, 1});

		r += 3.0f / 256.0f;
		g += 4.0f / 256.0f;
		b += 5.0f / 256.0f;

		if (r > 1.0f) { r = 0; }
		if (g > 1.0f) { g = 0; }
		if (b > 1.0f) { b = 0; }

		renderer.Begin();
		renderer.Clear();
		renderer.End();
	}

	return 0;
}
