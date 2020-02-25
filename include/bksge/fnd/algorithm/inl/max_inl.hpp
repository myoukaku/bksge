/**
 *	@file	max_inl.hpp
 *
 *	@brief	max の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MAX_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MAX_INL_HPP

#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/max_element.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <initializer_list>

namespace bksge
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
max(T const& a, T const& b)
{
	return bksge::max(a, b, bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CONSTEXPR T const&
max(T const& a, T const& b, Compare comp)
{
	return comp(b, a) ? a : b;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
max(std::initializer_list<T> t)
{
	return *bksge::max_element(t.begin(), t.end(), bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR T
max(std::initializer_list<T> t, Compare comp)
{
	return *bksge::max_element(t.begin(), t.end(), comp);
}

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MAX_INL_HPP
