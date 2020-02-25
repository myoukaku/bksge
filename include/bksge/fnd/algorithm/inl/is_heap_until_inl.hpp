/**
 *	@file	is_heap_until_inl.hpp
 *
 *	@brief	is_heap_until の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_HEAP_UNTIL_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_HEAP_UNTIL_INL_HPP

#include <bksge/fnd/algorithm/is_heap_until.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator, typename>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
is_heap_until(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	return bksge::algorithm::is_heap_until(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare, typename>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
is_heap_until(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using difference_type =
		bksge::iterator_difference_type<RandomAccessIterator>;

	difference_type const len = last - first;
	difference_type p = 0;
	difference_type c = 1;
	auto pp = first;

	while (c < len)
	{
		auto cp = first + c;
		
		if (comp(*pp, *cp))
		{
			return cp;
		}

		++c;
		++cp;
		
		if (c == len)
		{
			return last;
		}

		if (comp(*pp, *cp))
		{
			return cp;
		}

		++p;
		++pp;
		c = 2 * p + 1;
	}

	return last;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_HEAP_UNTIL_INL_HPP
