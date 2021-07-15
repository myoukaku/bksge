/**
 *	@file	vertex_layout_inl.hpp
 *
 *	@brief	VertexLayout の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_VERTEX_LAYOUT_INL_HPP
#define BKSGE_CORE_RENDER_INL_VERTEX_LAYOUT_INL_HPP

#include <bksge/core/render/vertex_layout.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

BKSGE_INLINE
VertexLayout::VertexLayout(void)
	: m_total_bytes(0)
{}

BKSGE_INLINE
VertexLayout::VertexLayout(VertexLayout&& rhs)
	: m_vertex_attribute_array(bksge::move(rhs.m_vertex_attribute_array))
	, m_total_bytes(bksge::move(rhs.m_total_bytes))
{}

BKSGE_INLINE VertexLayout&
VertexLayout::operator=(VertexLayout&& rhs)
{
	m_vertex_attribute_array = bksge::move(rhs.m_vertex_attribute_array);
	m_total_bytes            = bksge::move(rhs.m_total_bytes);
	return *this;
}

BKSGE_INLINE VertexAttribute const*
VertexLayout::FindVertexAttributeBySemantic(Semantic semantic) const
{
	for (auto&& attr : m_vertex_attribute_array)
	{
		if (attr.semantic() == semantic)
		{
			return &attr;
		}
	}

	return nullptr;
}

BKSGE_INLINE auto
VertexLayout::vertex_attribute_array(void) const
-> VertexAttributeArray const&
{
	return m_vertex_attribute_array;
}

BKSGE_INLINE std::size_t
VertexLayout::total_bytes(void) const
{
	return m_total_bytes;
}

BKSGE_INLINE void
VertexLayout::AddAttribute(VertexAttribute const& attribute)
{
	m_vertex_attribute_array.push_back(attribute);
	m_total_bytes += attribute.bytes();
}

BKSGE_INLINE bool
operator==(VertexLayout const& lhs, VertexLayout const& rhs)
{
	return lhs.m_total_bytes == rhs.m_total_bytes &&
		   lhs.m_vertex_attribute_array == rhs.m_vertex_attribute_array;
}

BKSGE_INLINE bool
operator!=(VertexLayout const& lhs, VertexLayout const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_VERTEX_LAYOUT_INL_HPP
