/**
 *	@file	includes_inl.hpp
 *
 *	@brief	includes の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_INCLUDES_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_INCLUDES_INL_HPP

#include <bksge/fnd/algorithm/includes.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename Compare,
	typename InputIterator1,
	typename InputIterator2
>
inline BKSGE_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	Compare comp)
{
	for (; first2 != last2; ++first1)
	{
		if (first1 == last1 || comp(*first2, *first1))
		{
			return false;
		}

		if (!comp(*first1, *first2))
		{
			++first2;
		}
	}

	return true;
}

}	// namespace detail

template <
	typename InputIterator1,
	typename InputIterator2
>
inline BKSGE_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	return bksge::includes(
		first1, last1, first2, last2, bksge::less<>());
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::includes<CompRef>(
		first1, last1, first2, last2, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_INCLUDES_INL_HPP
