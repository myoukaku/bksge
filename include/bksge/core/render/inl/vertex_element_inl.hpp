/**
 *	@file	vertex_element_inl.hpp
 *
 *	@brief	VertexElement の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_VERTEX_ELEMENT_INL_HPP
#define BKSGE_CORE_RENDER_INL_VERTEX_ELEMENT_INL_HPP

#include <bksge/core/render/vertex_element.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

template <typename T, std::size_t N, Semantic S>
inline auto VertexElement<T, N, S>::operator[](std::size_t index) const -> value_type const&
{
	return m_data[index];
}

template <typename T, std::size_t N, Semantic S>
inline auto VertexElement<T, N, S>::begin(void) const -> const_iterator
{
	return bksge::begin(m_data);
}

template <typename T, std::size_t N, Semantic S>
inline auto VertexElement<T, N, S>::end(void) const -> const_iterator
{
	return bksge::end(m_data);
}

template <typename T, std::size_t N, Semantic S>
inline bool operator==(VertexElement<T, N, S> const& lhs, VertexElement<T, N, S> const& rhs)
{
	return bksge::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, std::size_t N, Semantic S>
inline bool operator!=(VertexElement<T, N, S> const& lhs, VertexElement<T, N, S> const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_VERTEX_ELEMENT_INL_HPP
