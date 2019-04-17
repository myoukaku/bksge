/**
 *	@file	d3d11_hlsl_program_inl.hpp
 *
 *	@brief	D3D11HLSLProgram クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_HLSL_PROGRAM_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_HLSL_PROGRAM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_hlsl_program.hpp>
#include <bksge/render/d3d11/d3d11_hlsl_shader.hpp>
#include <bksge/render/d3d11/d3d11_geometry.hpp>
#include <bksge/render/d3d11/d3d11_renderer.hpp>
#include <bksge/render/shader.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/memory/make_unique.hpp>
#include <memory>
#include <string>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11HLSLProgram::D3D11HLSLProgram(D3D11Renderer* renderer, Shader const& shader)
{
	for (auto&& it : shader.program_map())
	{
		ShaderStage const stage = it.first;
		std::string const& source = it.second;

		std::unique_ptr<D3D11HLSLShaderBase> hlsl_shader;
		switch (stage)
		{
		case ShaderStage::kVertex:
			hlsl_shader = std::move(bksge::make_unique<D3D11HLSLVertexShader>());
			break;
		case ShaderStage::kGeometry:
			break;
		case ShaderStage::kFragment:
			hlsl_shader = std::move(bksge::make_unique<D3D11HLSLPixelShader>());
			break;
		case ShaderStage::kTessellationControl:
			break;
		case ShaderStage::kTessellationEvaluation:
			break;
		default:
			break;
		}

		if (hlsl_shader)
		{
			auto const ret = hlsl_shader->Compile(renderer, source);
			if (ret)
			{
				m_shaders.push_back(std::move(hlsl_shader));
			}
		}
	}
}

BKSGE_INLINE
D3D11HLSLProgram::~D3D11HLSLProgram()
{
}

BKSGE_INLINE void
D3D11HLSLProgram::Render(D3D11Renderer* renderer, D3D11Geometry const* geometry)
{
	geometry->Draw(renderer);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_HLSL_PROGRAM_INL_HPP
