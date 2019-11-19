﻿/**
 *	@file	hlsl_texture_fwd.hpp
 *
 *	@brief	HlslTexture の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_TEXTURE_FWD_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_TEXTURE_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

class HlslTexture;

using HlslTextureMap = std::map<Identifier, std::shared_ptr<HlslTexture>>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_DETAIL_FWD_HLSL_TEXTURE_FWD_HPP