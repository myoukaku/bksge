/**
 *	@file	box_geometry_inl.hpp
 *
 *	@brief	BoxGeometry クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_BOX_GEOMETRY_INL_HPP
#define BKSGE_CORE_DRAW_INL_BOX_GEOMETRY_INL_HPP

#include <bksge/core/draw/box_geometry.hpp>
#include <bksge/core/render/geometry.hpp>
//#include <bksge/core/shape/box.hpp>

namespace bksge
{

namespace draw
{

#if 0
template <typename T>
inline GeometryPtr MakeBoxGeometry(Box<T> const& box)
{
	auto const& min = box.Min();
	auto const& max = box.Max();

	Vertex<VPosition> const vertices[] =
	{
		{{{ min.x(), min.y(), min.z() }}},	// 0
		{{{ min.x(), min.y(), max.z() }}},	// 1
		{{{ min.x(), max.y(), min.z() }}},	// 2
		{{{ min.x(), max.y(), max.z() }}},	// 3
		{{{ max.x(), min.y(), min.z() }}},	// 4
		{{{ max.x(), min.y(), max.z() }}},	// 5
		{{{ max.x(), max.y(), min.z() }}},	// 6
		{{{ max.x(), max.y(), max.z() }}},	// 7
	};

	bksge::uint16_t const indices[] =
	{
		3, 1, 5,
		3, 5, 7,
		7, 5, 4,
		7, 4, 6,
		6, 4, 0,
		6, 0, 2,
		2, 0, 1,
		2, 1, 3,
		2, 3, 7,
		2, 7, 6,
		1, 0, 4,
		1, 4, 5,
	};

	return bksge::make_shared<Geometry>(
		Primitive::kTriangles, vertices, indices);
}
#endif

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_BOX_GEOMETRY_INL_HPP
