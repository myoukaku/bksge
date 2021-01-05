/**
 *	@file	minmax_inl.hpp
 *
 *	@brief	minmax の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MINMAX_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MINMAX_INL_HPP

#include <bksge/fnd/algorithm/minmax.hpp>
#include <bksge/fnd/algorithm/minmax_element.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/initializer_list.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::pair<T const&, T const&>
minmax(T const& a, T const& b)
{
	return bksge::minmax(a, b, bksge::less<>());
}

template <typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR bksge::pair<T const&, T const&>
minmax(T const& a, T const& b, Compare comp)
{
	return comp(a, b) ?
		bksge::pair<T const&, T const&>(a, b) :
		bksge::pair<T const&, T const&>(b, a);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::pair<T, T>
minmax(bksge::initializer_list<T> t)
{
	return bksge::minmax(t, bksge::less<>());
}

namespace detail
{

template <typename T, typename Iterator>
inline BKSGE_CONSTEXPR bksge::pair<T, T>
minmax_impl(bksge::pair<Iterator, Iterator> const& p)
{
	return bksge::pair<T, T>(*p.first, *p.second);
}

}	// namespace detail

template <typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR bksge::pair<T, T>
minmax(bksge::initializer_list<T> t, Compare comp)
{
	return detail::minmax_impl<T>(
		bksge::algorithm::minmax_element(t.begin(), t.end(), comp));
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MINMAX_INL_HPP
