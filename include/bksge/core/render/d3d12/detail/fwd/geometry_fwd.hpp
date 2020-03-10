/**
 *	@file	geometry_fwd.hpp
 *
 *	@brief	Geometry クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_GEOMETRY_FWD_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_GEOMETRY_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <map>

namespace bksge
{

namespace render
{

namespace d3d12
{

class Geometry;

using GeometryShared = bksge::shared_ptr<Geometry>;
using GeometryMap = std::map<Identifier, GeometryShared>;

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_FWD_GEOMETRY_FWD_HPP
