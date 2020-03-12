/**
 *	@file	geometry_fwd.hpp
 *
 *	@brief	Geometry の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_GEOMETRY_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_GEOMETRY_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

class Geometry;
using GeometryPtr = std::shared_ptr<Geometry>;

}	// namespace render

using render::Geometry;
using render::GeometryPtr;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_GEOMETRY_FWD_HPP
