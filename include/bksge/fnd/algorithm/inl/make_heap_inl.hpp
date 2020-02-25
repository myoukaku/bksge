/**
 *	@file	make_heap_inl.hpp
 *
 *	@brief	make_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MAKE_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MAKE_HEAP_INL_HPP

#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename RandomAccessIterator>
inline void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	auto n = last - first;
	
	if (n > 1)
	{
		// start from the first parent, there is no need to consider children
		for (auto start = (n - 2) / 2; start >= 0; --start)
		{
			detail::sift_down<Compare>(first, last, comp, n, first + start);
		}
	}
}

}	// namespace detail

template <typename RandomAccessIterator, typename>
inline void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::make_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare, typename>
inline void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	detail::make_heap<CompRef>(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MAKE_HEAP_INL_HPP
