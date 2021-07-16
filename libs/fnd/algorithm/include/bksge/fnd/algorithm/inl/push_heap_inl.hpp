/**
 *	@file	push_heap_inl.hpp
 *
 *	@brief	push_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PUSH_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PUSH_HEAP_INL_HPP

#include <bksge/fnd/algorithm/push_heap.hpp>
#include <bksge/fnd/algorithm/detail/push_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::push_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using value_t = bksge::iter_value_t<RandomAccessIterator>;
	using difference_t = bksge::iter_difference_t<RandomAccessIterator>;

	value_t value = std::move(*(last - 1));
	detail::push_heap(
		first,
		difference_t((last - first) - 1),
		difference_t(0),
		std::move(value),
		comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PUSH_HEAP_INL_HPP
