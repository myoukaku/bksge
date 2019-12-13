/**
 *	@file	vertex_attribute_inl.hpp
 *
 *	@brief	VertexAttribute の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ATTRIBUTE_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ATTRIBUTE_INL_HPP

#include <bksge/core/render/detail/vertex_attribute.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

BKSGE_INLINE
VertexAttribute::VertexAttribute(
	Semantic semantic,
	TypeEnum type,
	std::size_t element_num,
	std::size_t offset)
	: m_semantic(semantic)
	, m_type(type)
	, m_element_num(element_num)
	, m_offset(offset)
{}

BKSGE_INLINE
Semantic VertexAttribute::semantic(void) const
{
	return m_semantic;
}

BKSGE_INLINE
TypeEnum VertexAttribute::type(void) const
{
	return m_type;
}

BKSGE_INLINE
std::size_t VertexAttribute::element_num(void) const
{
	return m_element_num;
}

BKSGE_INLINE
std::size_t VertexAttribute::offset(void) const
{
	return m_offset;
}

BKSGE_INLINE
std::size_t VertexAttribute::bytes(void) const
{
	return element_num() * GetSizeOf(type());
}

BKSGE_INLINE
bool operator==(VertexAttribute const& lhs, VertexAttribute const& rhs)
{
	return
		lhs.semantic()    == rhs.semantic()    &&
		lhs.type()        == rhs.type()        &&
		lhs.element_num() == rhs.element_num() &&
		lhs.offset()      == rhs.offset();
}

BKSGE_INLINE
bool operator!=(VertexAttribute const& lhs, VertexAttribute const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ATTRIBUTE_INL_HPP
