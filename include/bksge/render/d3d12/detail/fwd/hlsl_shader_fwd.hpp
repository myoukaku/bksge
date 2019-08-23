/**
 *	@file	hlsl_shader_fwd.hpp
 *
 *	@brief	HLSLShader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_FWD_HLSL_SHADER_FWD_HPP
#define BKSGE_RENDER_D3D12_DETAIL_FWD_HLSL_SHADER_FWD_HPP

#include <bksge/render/shader_stage.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class HLSLShaderBase;
class HLSLVertexShader;
class HLSLPixelShader;

using HLSLShaderMap =
	std::map<ShaderStage, std::unique_ptr<HLSLShaderBase>>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_DETAIL_FWD_HLSL_SHADER_FWD_HPP
