/**
 *	@file	d3d11_geometry_fwd.hpp
 *
 *	@brief	D3D11Geometry の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_FWD_D3D11_GEOMETRY_FWD_HPP
#define BKSGE_RENDER_D3D11_FWD_D3D11_GEOMETRY_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D11Geometry;

using D3D11GeometryShared = std::shared_ptr<D3D11Geometry>;
using D3D11GeometryMap = std::map<Identifier, D3D11GeometryShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D11_FWD_D3D11_GEOMETRY_FWD_HPP
