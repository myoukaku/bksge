/**
 *	@file	index_array_inl.hpp
 *
 *	@brief	IndexArray の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_INDEX_ARRAY_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_INDEX_ARRAY_INL_HPP

#include <bksge/core/render/detail/index_array.hpp>
#include <bksge/core/render/detail/type_enum.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace render
{

template <typename T>
inline IndexArray<T>::IndexArray(void)
{}

template <typename T>
template <typename Iterator>
inline IndexArray<T>::IndexArray(Iterator first, Iterator last)
	: m_value(first, last)
{}

template <typename T>
inline TypeEnum IndexArray<T>::type(void) const
{
	return TypeToEnum<T>::value;
}

template <typename T>
inline auto IndexArray<T>::data(void) const -> const_pointer
{
	return m_value.empty() ? nullptr : m_value.data();
}

template <typename T>
inline auto IndexArray<T>::bytes(void) const -> size_type
{
	return count() * GetSizeOf(type());
}

template <typename T>
inline auto IndexArray<T>::count(void) const -> size_type
{
	return m_value.size();
}

template <typename T>
inline T const& IndexArray<T>::operator[](bksge::size_t i) const
{
	return m_value[i];
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_INDEX_ARRAY_INL_HPP
