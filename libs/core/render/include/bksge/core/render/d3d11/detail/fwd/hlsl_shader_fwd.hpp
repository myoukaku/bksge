/**
 *	@file	hlsl_shader_fwd.hpp
 *
 *	@brief	HlslShader の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_HLSL_SHADER_FWD_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_HLSL_SHADER_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

class HlslShaderBase;

using HlslShaderUnique = bksge::unique_ptr<HlslShaderBase>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_FWD_HLSL_SHADER_FWD_HPP
