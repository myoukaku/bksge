/**
 *	@file	find_first_of_inl.hpp
 *
 *	@brief	find_first_of の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_FIND_FIRST_OF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_FIND_FIRST_OF_INL_HPP

#include <bksge/fnd/algorithm/find_first_of.hpp>
#include <bksge/fnd/functional/equal_to.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename ForwardIterator
>
inline BKSGE_CXX14_CONSTEXPR InputIterator
find_first_of(
	InputIterator first1,
	InputIterator last1,
	ForwardIterator first2,
	ForwardIterator last2)
{
	return bksge::algorithm::find_first_of(
		first1, last1, first2, last2, bksge::equal_to<>());
}

template <
	typename InputIterator,
	typename ForwardIterator,
	typename BinaryPredicate
>
inline BKSGE_CXX14_CONSTEXPR InputIterator
find_first_of(
	InputIterator first1,
	InputIterator last1,
	ForwardIterator first2,
	ForwardIterator last2,
	BinaryPredicate pred)
{
	for (; first1 != last1; ++first1)
	{
		for (auto it = first2; it != last2; ++it)
		{
			if (pred(*first1, *it))
			{
				return first1;
			}
		}
	}

	return last1;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_FIND_FIRST_OF_INL_HPP
