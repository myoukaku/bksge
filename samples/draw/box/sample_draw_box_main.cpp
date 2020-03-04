/**
 *	@file	sample_draw_box_main.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/core/window.hpp>
#include <bksge/core/draw.hpp>
#include <bksge/core/render.hpp>
#include <bksge/fnd/units/degree.hpp>
#include <memory>

namespace
{

#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER
using DefaultRenderer = bksge::D3D12Renderer;
#elif BKSGE_CORE_RENDER_HAS_D3D11_RENDERER
using DefaultRenderer = bksge::D3D11Renderer;
#elif BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER
using DefaultRenderer = bksge::VulkanRenderer;
#elif BKSGE_CORE_RENDER_HAS_GL_RENDERER
using DefaultRenderer = bksge::GlRenderer;
#else
using DefaultRenderer = bksge::NullRenderer;
#endif

using Degreesf = bksge::units::degrees<float>;

}	// namespace

int main()
{
	bksge::Window window({800, 600}, "sample_draw_box");
	DefaultRenderer renderer(window);

	bksge::Scene scene;

	{
		auto const fovy = Degreesf(45);
		auto const aspect = 4.0f / 3.0f;
		auto const near_z = 0.1f;
		auto const far_z = 1000.0f;
		auto camera = std::make_shared<bksge::PerspectiveCamera>(
			fovy, aspect, near_z, far_z);
		camera->SetPosition({0, 5, 10});
		camera->LookAt({0, 0, 0});

		scene.Add(camera);
	}

	while (window.Update())
	{
		renderer.Begin();
		
		scene.Render(&renderer);
		
		renderer.End();
	}

	return 0;
}
