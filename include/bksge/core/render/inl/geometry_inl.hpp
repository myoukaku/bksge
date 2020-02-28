/**
 *	@file	geometry_inl.hpp
 *
 *	@brief	Geometry の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_GEOMETRY_INL_HPP
#define BKSGE_CORE_RENDER_INL_GEOMETRY_INL_HPP

#include <bksge/core/render/geometry.hpp>
#include <bksge/core/render/vertex.hpp>
#include <bksge/core/render/vertex_element.hpp>
#include <bksge/core/render/vertex_layout.hpp>
#include <bksge/core/render/detail/type_enum.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Geometry::Geometry(void)
	: m_primitive_topology(PrimitiveTopology::kTriangles)
	, m_vertex_array()
	, m_index_array()
{}

BKSGE_INLINE PrimitiveTopology const&
Geometry::primitive_topology(void) const
{
	return m_primitive_topology;
}

BKSGE_INLINE VertexLayout const&
Geometry::vertex_layout(void) const
{
	static VertexLayout const dummy;

	return m_vertex_array ? m_vertex_array->vertex_layout() : dummy;
}

BKSGE_INLINE void const*
Geometry::vertex_array_data(void) const
{
	return m_vertex_array ? m_vertex_array->data() : nullptr;
}

BKSGE_INLINE bksge::size_t
Geometry::vertex_array_bytes(void) const
{
	return m_vertex_array ? m_vertex_array->bytes() : 0;
}

BKSGE_INLINE bksge::size_t
Geometry::vertex_array_count(void) const
{
	return m_vertex_array ? m_vertex_array->count() : 0;
}

BKSGE_INLINE void const*
Geometry::index_array_data(void) const
{
	return m_index_array ? m_index_array->data() : nullptr;
}

BKSGE_INLINE bksge::size_t
Geometry::index_array_bytes(void) const
{
	return m_index_array ? m_index_array->bytes() : 0;
}

BKSGE_INLINE bksge::size_t
Geometry::index_array_count(void) const
{
	return m_index_array ? m_index_array->count() : 0;
}

BKSGE_INLINE TypeEnum
Geometry::index_array_type(void) const
{
	return m_index_array ? m_index_array->type() : TypeEnum::kUInt16;
}

namespace geometry_detail
{

template <typename Ptr> inline bool
PointerDeepCompare(Ptr const& lhs, Ptr const& rhs)
{
	if (lhs == rhs)
	{
		return true;
	}

	if (lhs == nullptr ||
		rhs == nullptr)
	{
		return false;
	}

	return *lhs == *rhs;
}

}	// namespace geometry_detail

BKSGE_INLINE bool
operator==(Geometry const& lhs, Geometry const& rhs)
{
	return
		lhs.m_primitive_topology == rhs.m_primitive_topology &&
		geometry_detail::PointerDeepCompare(lhs.m_vertex_array, rhs.m_vertex_array) &&
		geometry_detail::PointerDeepCompare(lhs.m_index_array,  rhs.m_index_array);
}

BKSGE_INLINE bool
operator!=(Geometry const& lhs, Geometry const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_GEOMETRY_INL_HPP
