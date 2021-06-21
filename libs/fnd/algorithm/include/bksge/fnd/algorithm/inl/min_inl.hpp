/**
 *	@file	min_inl.hpp
 *
 *	@brief	min の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MIN_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MIN_INL_HPP

#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/algorithm/min_element.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>

namespace bksge
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
min(T const& a, T const& b)
{
	return bksge::min(a, b, bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CONSTEXPR T const&
min(T const& a, T const& b, Compare comp)
{
	return comp(a, b) ? a : b;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
min(std::initializer_list<T> t)
{
	return *bksge::min_element(t.begin(), t.end(), bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR T
min(std::initializer_list<T> t, Compare comp)
{
	return *bksge::min_element(t.begin(), t.end(), comp);
}

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MIN_INL_HPP
