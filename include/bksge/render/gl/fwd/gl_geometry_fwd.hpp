/**
 *	@file	gl_geometry_fwd.hpp
 *
 *	@brief	GlGeometry クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_GEOMETRY_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_GEOMETRY_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class GlGeometry;
using GlGeometryShared = std::shared_ptr<GlGeometry>;
using GlGeometryMap    = std::map<Identifier, GlGeometryShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_GEOMETRY_FWD_HPP
