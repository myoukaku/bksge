/**
 *	@file	d3d11_hlsl_program.hpp
 *
 *	@brief	D3D11HLSLProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_HLSL_PROGRAM_HPP
#define BKSGE_RENDER_D3D11_D3D11_HLSL_PROGRAM_HPP

#include <bksge/render/d3d11/fwd/d3d11_hlsl_program_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_hlsl_shader_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_context_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11HLSLProgram
{
public:
	D3D11HLSLProgram(D3D11Device* device, Shader const& shader);

	~D3D11HLSLProgram();

	void Render(D3D11DeviceContext* device_context, D3D11Geometry const* geometry);

private:
	using D3D11HLSLShaders = std::vector<D3D11HLSLShaderUnique>;

	D3D11HLSLShaders	m_shaders;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_hlsl_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_HLSL_PROGRAM_HPP
