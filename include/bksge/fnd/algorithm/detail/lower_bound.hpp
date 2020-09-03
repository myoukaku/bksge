/**
 *	@file	lower_bound.hpp
 *
 *	@brief	lower_bound の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_LOWER_BOUND_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_LOWER_BOUND_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename ForwardIterator, typename T, typename Compare>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
lower_bound(
	ForwardIterator first,
	ForwardIterator last,
	const T& val,
	Compare comp)
{
	using difference_t = bksge::iter_difference_t<ForwardIterator>;

	difference_t len = bksge::distance(first, last);

	while (len > 0)
	{
		difference_t half = len >> 1;
		auto middle = first;
		bksge::advance(middle, half);

		if (comp(*middle, val))
		{
			first = middle;
			++first;
			len = len - half - 1;
		}
		else
		{
			len = half;
		}
	}

	return first;
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_LOWER_BOUND_HPP
