/**
 *	@file	pop_heap.hpp
 *
 *	@brief	pop_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_POP_HEAP_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_POP_HEAP_HPP

#include <bksge/fnd/algorithm/detail/adjust_heap.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	RandomAccessIterator result,
	Compare& comp)
{
	using value_t = bksge::iter_value_t<RandomAccessIterator>;
	using difference_t = bksge::iter_difference_t<RandomAccessIterator>;

	value_t value = bksge::move(*result);
	*result = bksge::move(*first);
	detail::adjust_heap(
		first,
		difference_t(0),
		difference_t(last - first),
		bksge::move(value),
		comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_POP_HEAP_HPP
