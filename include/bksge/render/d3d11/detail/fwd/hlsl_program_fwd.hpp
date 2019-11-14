﻿/**
 *	@file	hlsl_program_fwd.hpp
 *
 *	@brief	HlslProgram の前方宣言
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

class HlslProgram;

using HlslProgramShared = std::shared_ptr<HlslProgram>;
using HlslProgramMap = std::map<Identifier, HlslProgramShared>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_PROGRAM_FWD_HPP
