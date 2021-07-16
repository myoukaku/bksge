/**
 *	@file	rotate_inl.hpp
 *
 *	@brief	rotate の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_ROTATE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_ROTATE_INL_HPP

#include <bksge/fnd/algorithm/rotate.hpp>
#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/algorithm/swap_ranges.hpp>
#include <bksge/fnd/numeric/gcd.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/iterator_category.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_assignable.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename ForwardIterator>
inline ForwardIterator
rotate_left(
	ForwardIterator first,
	ForwardIterator last)
{
	auto tmp = std::move(*first);
	auto lm1 = bksge::move(bksge::next(first), last, first);
	*lm1 = std::move(tmp);
	return lm1;
}

template <typename BidirectionalIterator>
inline BidirectionalIterator
rotate_right(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	auto lm1 = bksge::prev(last);
	auto tmp = std::move(*lm1);
	auto fp1 = bksge::move_backward(first, lm1, last);
	*first = std::move(tmp);
	return fp1;
}

template <typename ForwardIterator>
inline ForwardIterator
rotate_forward(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last)
{
	auto i = middle;

	for (;;)
	{
		swap(*first, *i);
		++first;

		if (++i == last)
		{
			break;
		}

		if (first == middle)
		{
			middle = i;
		}
	}

	auto const r = first;
	
	if (first != middle)
	{
		i = middle;

		for (;;)
		{
			swap(*first, *i);
			++first;

			if (++i == last)
			{
				if (first == middle)
				{
					break;
				}

				i = middle;
			}
			else if (first == middle)
			{
				middle = i;
			}
		}
	}

	return r;
}

template <typename RandomAccessIterator>
inline RandomAccessIterator
rotate_gcd(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last)
{
	auto const m1 = middle - first;
	auto const m2 = last - middle;

	if (m1 == m2)
	{
		bksge::swap_ranges(first, middle, middle);
		return middle;
	}

	auto const g = bksge::gcd(m1, m2);

	for (auto p = first + g; p != first;)
	{
		auto t = std::move(*--p);
		auto p1 = p;
		auto p2 = p1 + m1;

		do
		{
			*p1 = std::move(*p2);
			p1 = p2;
			auto const d = last - p2;

			if (m1 < d)
			{
				p2 += m1;
			}
			else
			{
				p2 = first + (m1 - d);
			}
		}
		while (p2 != p);
		
		*p1 = std::move(t);
	}

	return first + m2;
}

template <typename ForwardIterator>
inline ForwardIterator
rotate(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	bksge::forward_iterator_tag*,
	bksge::false_type)
{
	return rotate_forward(first, middle, last);
}

template <typename ForwardIterator>
inline ForwardIterator
rotate(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	bksge::forward_iterator_tag*,
	bksge::true_type)
{
	if (bksge::next(first) == middle)
	{
		return rotate_left(first, last);
	}

	return rotate_forward(first, middle, last);
}

template <typename BidirectionalIterator>
inline BidirectionalIterator
rotate(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	bksge::bidirectional_iterator_tag*,
	bksge::true_type)
{
	if (bksge::next(first) == middle)
	{
		return rotate_left(first, last);
	}

	if (bksge::next(middle) == last)
	{
		return rotate_right(first, last);
	}

	return rotate_forward(first, middle, last);
}

template <typename RandomAccessIterator>
inline RandomAccessIterator
rotate(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	bksge::random_access_iterator_tag*,
	bksge::true_type)
{
	if (bksge::next(first) == middle)
	{
		return rotate_left(first, last);
	}

	if (bksge::next(middle) == last)
	{
		return rotate_right(first, last);
	}

	return rotate_gcd(first, middle, last);
}

}	// namespace detail

template <typename ForwardIterator>
inline ForwardIterator
rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
{
	if (first == middle)
	{
		return last;
	}

	if (middle == last)
	{
		return first;
	}

	using Category = bksge::iterator_category<ForwardIterator>*;
	using ValueType = bksge::iter_value_t<ForwardIterator>;

	return bksge::algorithm::detail::rotate(
		first, middle, last, Category(),
		bksge::is_trivially_move_assignable<ValueType>());
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_ROTATE_INL_HPP
