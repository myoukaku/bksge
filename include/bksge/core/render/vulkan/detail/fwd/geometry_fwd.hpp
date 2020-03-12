/**
 *	@file	geometry_fwd.hpp
 *
 *	@brief	Geometry クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_GEOMETRY_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_GEOMETRY_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <memory>
#include <map>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Geometry;

using GeometrySharedPtr = std::shared_ptr<Geometry>;
using GeometrySharedPtrMap = std::map<Identifier, GeometrySharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_GEOMETRY_FWD_HPP
