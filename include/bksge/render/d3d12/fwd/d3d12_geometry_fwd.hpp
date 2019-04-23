/**
 *	@file	d3d12_geometry_fwd.hpp
 *
 *	@brief	D3D12Geometry クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_FWD_D3D12_GEOMETRY_FWD_HPP
#define BKSGE_RENDER_D3D12_FWD_D3D12_GEOMETRY_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class D3D12Geometry;

using D3D12GeometryShared = std::shared_ptr<D3D12Geometry>;
using D3D12GeometryMap = std::map<Identifier, D3D12GeometryShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_D3D12_FWD_D3D12_GEOMETRY_FWD_HPP
