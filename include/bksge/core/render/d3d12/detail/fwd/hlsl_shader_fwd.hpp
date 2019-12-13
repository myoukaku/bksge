/**
 *	@file	hlsl_shader_fwd.hpp
 *
 *	@brief	HlslShader クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_HLSL_SHADER_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_HLSL_SHADER_FWD_HPP

#include <bksge/core/render/shader_stage.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d12
{

class HlslShaderBase;
class HlslVertexShader;
class HlslPixelShader;

using HlslShaderMap =
	std::map<ShaderStage, std::unique_ptr<HlslShaderBase>>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_HLSL_SHADER_FWD_HPP
