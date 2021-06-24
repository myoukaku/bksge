/**
 *	@file	geometry_fwd.hpp
 *
 *	@brief	Geometry クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_FWD_GEOMETRY_FWD_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_FWD_GEOMETRY_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/map/map.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

class Geometry;
using GeometryShared = bksge::shared_ptr<Geometry>;
using GeometryMap    = bksge::map<Identifier, GeometryShared>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_GL_DETAIL_FWD_GEOMETRY_FWD_HPP
