/**
 *	@file	box_geometry.hpp
 *
 *	@brief	BoxGeometry クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_BOX_GEOMETRY_HPP
#define BKSGE_CORE_DRAW_BOX_GEOMETRY_HPP

#include <bksge/core/draw/fwd/box_geometry_fwd.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/core/math/vector3.hpp>
//#include <bksge/core/shape/fwd/box_fwd.hpp>

namespace bksge
{

namespace draw
{

class BoxGeometry : public Geometry
{
public:
	/**
	 *	@brief	点を表す型
	 */
	using PointType = bksge::Vector3<float>;

	BoxGeometry(PointType const& p1, PointType const& p2);
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/box_geometry_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_BOX_GEOMETRY_HPP
