/**
 *	@file	vertex_attribute.hpp
 *
 *	@brief	VertexAttribute の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_VERTEX_ATTRIBUTE_HPP
#define BKSGE_CORE_RENDER_DETAIL_VERTEX_ATTRIBUTE_HPP

#include <bksge/core/render/semantic.hpp>
#include <bksge/core/render/detail/type_enum.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

/**
 *	@brief	1つの頂点のうちの1要素
 */
class VertexAttribute
{
public:
	VertexAttribute(
		Semantic semantic,
		TypeEnum type,
		std::size_t element_num,
		std::size_t offset);

	Semantic    semantic(void) const;
	TypeEnum    type(void) const;
	std::size_t element_num(void) const;
	std::size_t offset(void) const;
	std::size_t bytes(void) const;

private:
	Semantic    m_semantic;
	TypeEnum    m_type;
	std::size_t m_element_num;
	std::size_t m_offset;
};

bool operator==(VertexAttribute const& lhs, VertexAttribute const& rhs);
bool operator!=(VertexAttribute const& lhs, VertexAttribute const& rhs);

/**
 *	@brief
 */
template <typename T>
inline VertexAttribute MakeVertexAttribute(std::size_t offset)
{
	return { T::semantic, T::type_enum, T::element_num, offset };
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/detail/inl/vertex_attribute_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DETAIL_VERTEX_ATTRIBUTE_HPP
