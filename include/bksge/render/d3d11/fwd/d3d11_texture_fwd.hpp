/**
 *	@file	d3d11_texture_fwd.hpp
 *
 *	@brief	D3D11Texture の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_FWD_D3D11_TEXTURE_FWD_HPP
#define BKSGE_RENDER_D3D11_FWD_D3D11_TEXTURE_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D11Texture;

using D3D11TextureMap = std::map<Identifier, std::shared_ptr<D3D11Texture>>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_FWD_D3D11_TEXTURE_FWD_HPP
