/**
 *	@file	d3d11_hlsl_shader_fwd.hpp
 *
 *	@brief	D3D11HLSLShader の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_FWD_D3D11_HLSL_SHADER_FWD_HPP
#define BKSGE_RENDER_D3D11_FWD_D3D11_HLSL_SHADER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

class D3D11HLSLShaderBase;

using D3D11HLSLShaderUnique = std::unique_ptr<D3D11HLSLShaderBase>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_FWD_D3D11_HLSL_SHADER_FWD_HPP
