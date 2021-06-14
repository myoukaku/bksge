/**
 *	@file	lexicographical_compare_inl.hpp
 *
 *	@brief	lexicographical_compare の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_LEXICOGRAPHICAL_COMPARE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_LEXICOGRAPHICAL_COMPARE_INL_HPP

#include <bksge/fnd/algorithm/lexicographical_compare.hpp>
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
lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp)
{
	for (; first2 != last2; ++first1, (void) ++first2)
	{
		if (first1 == last1 || comp(*first1, *first2))
		{
			return true;
		}

		if (comp(*first2, *first1))
		{
			return false;
		}
	}

	return false;
}

}	// namespace detail

template <
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR bool
lexicographical_compare(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::lexicographical_compare<CompRef>(
		first1, last1, first2, last2, comp);
}

template <
	typename InputIterator1,
	typename InputIterator2
>
inline BKSGE_CXX14_CONSTEXPR bool
lexicographical_compare(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2)
{
	return bksge::algorithm::lexicographical_compare(
		first1, last1, first2, last2, bksge::less<>());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_LEXICOGRAPHICAL_COMPARE_INL_HPP
