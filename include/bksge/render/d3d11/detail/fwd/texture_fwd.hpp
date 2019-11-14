/**
 *	@file	texture_fwd.hpp
 *
 *	@brief	Texture の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_FWD_TEXTURE_FWD_HPP
#define BKSGE_RENDER_D3D11_DETAIL_FWD_TEXTURE_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace d3d11
{

class Texture;

using TextureShared = std::shared_ptr<Texture>;
using TextureMap = std::map<Identifier, TextureShared>;

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_DETAIL_FWD_TEXTURE_FWD_HPP
