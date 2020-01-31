/**
 *	@file	renderer_inl.hpp
 *
 *	@brief	Renderer の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_RENDERER_INL_HPP
#define BKSGE_CORE_RENDER_INL_RENDERER_INL_HPP

#include <bksge/core/render/renderer.hpp>
#include <bksge/core/render/shader.hpp>
#include <vector>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Renderer::Renderer(void)
{}

BKSGE_INLINE
Renderer::~Renderer()
{}

BKSGE_INLINE
void Renderer::Begin(void)
{
	VBegin();
}

BKSGE_INLINE
void Renderer::End(void)
{
	VEnd();
}

BKSGE_INLINE
void Renderer::BeginRenderPass(RenderPassInfo const& render_pass_info)
{
	VBeginRenderPass(render_pass_info);
}

BKSGE_INLINE
void Renderer::EndRenderPass(void)
{
	VEndRenderPass();
}

BKSGE_INLINE
void Renderer::Render(
	Geometry const& geometry,
	std::vector<Shader const*> const& shader_list,
	ShaderParameterMap const& shader_parameter_map,
	RenderState const& render_state)
{
	for (auto&& shader : shader_list)
	{
		if (shader)
		{
			if (VRender(geometry, *shader, shader_parameter_map, render_state))
			{
				break;
			}
		}
	}
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_RENDERER_INL_HPP
