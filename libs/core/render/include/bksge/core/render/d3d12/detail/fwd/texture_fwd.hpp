/**
 *	@file	texture_fwd.hpp
 *
 *	@brief	Texture の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_TEXTURE_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_TEXTURE_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/map/map.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Texture;

using TextureShared = bksge::shared_ptr<Texture>;
using TextureMap = bksge::map<Identifier, TextureShared>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_TEXTURE_FWD_HPP
