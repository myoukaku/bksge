/**
 *	@file	d3d12_hlsl_shader_fwd.hpp
 *
 *	@brief	D3D12HLSLShader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_FWD_D3D12_HLSL_SHADER_FWD_HPP
#define BKSGE_RENDER_D3D12_FWD_D3D12_HLSL_SHADER_FWD_HPP

#include <bksge/render/shader_stage.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D12HLSLShaderBase;
class D3D12HLSLVertexShader;
class D3D12HLSLPixelShader;

using D3D12HLSLShaderMap =
	std::map<ShaderStage, std::unique_ptr<D3D12HLSLShaderBase>>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_FWD_D3D12_HLSL_SHADER_FWD_HPP
