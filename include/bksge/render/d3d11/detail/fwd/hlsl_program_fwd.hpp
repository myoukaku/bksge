/**
 *	@file	hlsl_program_fwd.hpp
 *
 *	@brief	HLSLProgram の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

class HLSLProgram;

using HLSLProgramMap = std::map<Identifier, std::shared_ptr<HLSLProgram>>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP
