/**
 *	@file	hlsl_shader_fwd.hpp
 *
 *	@brief	HLSLShader の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_SHADER_FWD_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_SHADER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

class HLSLShaderBase;

using HLSLShaderUnique = std::unique_ptr<HLSLShaderBase>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_SHADER_FWD_HPP
