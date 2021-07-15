/**
 *	@file	radix_sort.hpp
 *
 *	@brief	radix_sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RADIX_SORT_HPP
#define BKSGE_FND_ALGORITHM_RADIX_SORT_HPP

#include <bksge/fnd/algorithm/swap_ranges.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/bit/countr_zero.hpp>
#include <bksge/fnd/bit/has_single_bit.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

template <
	std::size_t Radix,
	typename Iter1,
	typename Iter2,
	typename Proj,
	typename SizeType
>
inline BKSGE_CXX14_CONSTEXPR void
radix_sort_loop(Iter1 input, Iter2 output, Proj proj, SizeType size, std::size_t shift)
{
	std::size_t const Mask = Radix - 1;

	std::size_t counts[Radix] = {};

	// Count occurrences
	for (SizeType i = 0; i < size; ++i)
	{
		auto const idx = (bksge::invoke(proj, input[i]) >> shift) & Mask;
		counts[idx]++;
	}

	// Prefix Sum
	for (std::size_t i = 1; i < Radix; ++i)
	{
		counts[i] += counts[i - 1];
	}

	// Build the output array
	for (auto i = size - 1; i >= 0; --i)
	{
		auto const idx = (bksge::invoke(proj, input[i]) >> shift) & Mask;
		output[--counts[idx]] = bksge::move(input[i]);
	}
}

}	// namespace detail

template <
	typename RandomAccessIterator,
	typename Proj = bksge::identity
>
inline BKSGE_CXX14_CONSTEXPR void
radix_sort(RandomAccessIterator first, RandomAccessIterator last, Proj proj = {})
{
	std::size_t const Radix = 0x100;
	static_assert(bksge::has_single_bit(Radix), "");

	using value_t = bksge::iter_value_t<RandomAccessIterator>;
	auto const size = bksge::ranges::distance(first, last);
	bksge::vector<value_t> tmp(size);

	int loop_count = 0;
	for (std::size_t shift = 0;
		shift < bksge::bitsof<value_t>();
		shift += bksge::countr_zero(Radix))
	{
		if (loop_count % 2 == 0)
		{
			detail::radix_sort_loop<Radix>(first, tmp.begin(), proj, size, shift);
		}
		else
		{
			detail::radix_sort_loop<Radix>(tmp.begin(), first, proj, size, shift);
		}

		++loop_count;
	}

	// Make sure original range is output
	if (loop_count % 2 == 1)
	{
		bksge::swap_ranges(
			first, last,
			tmp.begin(), tmp.end());
	}
}

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RADIX_SORT_HPP
