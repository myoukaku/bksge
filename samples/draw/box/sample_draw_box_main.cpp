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
#include <bksge/core/math.hpp>
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

	// setup cameras
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
	// setup lights
	{
		{
			auto light = std::make_shared<bksge::AmbientLight>();
			scene.Add(light);
			light->SetColor(bksge::Color3f{1, 1, 0});
			light->SetIntensity(1);
		}
		{
			auto light = std::make_shared<bksge::DirectionalLight>();
			scene.Add(light);
			light->SetColor({1, 1, 0});
			light->SetIntensity(1);
			light->SetPosition({1, 1, 0});
			light->LookAt({0, 0, 0});
		}
	}
	// setup meshes
	{
		auto box_geometry = std::make_shared<bksge::BoxGeometry>(
			bksge::Vector3f{-1.5,-0.5,-1.5}, bksge::Vector3f{0.5,2.5,1.5});

		auto simple_material = std::make_shared<bksge::SimpleMaterial>();
		simple_material->SetDiffuseColor(bksge::Color3f{1, 1, 0});
		simple_material->SetOpacity(1);

		auto mesh = std::make_shared<bksge::Mesh>(box_geometry, simple_material);
		scene.Add(mesh);
	}

	while (window.Update())
	{
		renderer.Begin();
		
		scene.Render(&renderer);
		
		renderer.End();
	}

	return 0;
}
