﻿/**
 *	@file	vertex_array_inl.hpp
 *
 *	@brief	VertexArray の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ARRAY_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ARRAY_INL_HPP

#include <bksge/core/render/detail/vertex_array.hpp>
#include <bksge/core/render/vertex_layout.hpp>

namespace bksge
{

namespace render
{

template <typename T>
inline VertexArray<T>::VertexArray(void)
{}

template <typename T>
template <typename Iterator>
inline VertexArray<T>::VertexArray(Iterator first, Iterator last)
	: m_value(first, last)
{}

template <typename T>
inline VertexLayout const& VertexArray<T>::vertex_layout(void) const
{
	return m_layout;
}

template <typename T>
inline auto VertexArray<T>::data(void) const -> const_pointer
{
	return m_value.empty() ? nullptr : m_value.data();
}

template <typename T>
inline auto VertexArray<T>::bytes(void) const -> size_type
{
	return vertex_layout().total_bytes() * m_value.size();
}

template <typename T>
inline auto VertexArray<T>::count(void) const -> size_type
{
	return m_value.size();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_VERTEX_ARRAY_INL_HPP
