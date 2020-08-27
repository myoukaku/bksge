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
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename Compare, typename RandomAccessIterator, typename DifferenceType>
inline BKSGE_CXX14_CONSTEXPR void
sift_up(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp,
	DifferenceType len)
{
	using value_type = bksge::iter_value_t<RandomAccessIterator>;

	if (len > 1)
	{
		len = (len - 2) / 2;
		auto ptr = first + len;

		if (comp(*ptr, *--last))
		{
			value_type t(bksge::move(*last));

			do
			{
				*last = bksge::move(*ptr);
				last = ptr;

				if (len == 0)
				{
					break;
				}

				len = (len - 1) / 2;
				ptr = first + len;
			}
			while (comp(*ptr, t));

			*last = bksge::move(t);
		}
	}
}

}	// namespace detail

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
	using CompRef = bksge::add_lvalue_reference_t<Compare>;
	detail::sift_up<CompRef>(first, last, comp, last - first);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PUSH_HEAP_INL_HPP
