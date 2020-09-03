/**
 *	@file	set_intersection_inl.hpp
 *
 *	@brief	set_intersection の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SET_INTERSECTION_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SET_INTERSECTION_INL_HPP

#include <bksge/fnd/algorithm/set_intersection.hpp>
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
	typename InputIterator2,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
set_intersection(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	Compare comp)
{
	while (first1 != last1 && first2 != last2)
	{
		if (comp(*first1, *first2))
		{
			++first1;
		}
		else
		{
			if (!comp(*first2, *first1))
			{
				*result = *first1;
				++result;
				++first1;
			}

			++first2;
		}
	}

	return result;
}

}	// namespace detail

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
set_intersection(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	OutputIterator result)
{
	return bksge::algorithm::set_intersection(
		first1, last1, first2, last2, result, bksge::less<>());
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
set_intersection(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	OutputIterator result,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	return detail::set_intersection<CompRef>(
		first1, last1, first2, last2, result, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SET_INTERSECTION_INL_HPP
