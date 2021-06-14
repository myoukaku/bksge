/**
 *	@file	reverse.hpp
 *
 *	@brief	ranges::reverse の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REVERSE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REVERSE_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct reverse_fn
{
private:
	template <
		BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iter),
		typename Sent
	>
	static BKSGE_CXX14_CONSTEXPR Iter
	impl(Iter first, Sent last,
		bksge::detail::overload_priority<1>)
	{
		auto i = ranges::next(first, last);
		auto tail = i;

		if (first != last)
		{
			--tail;
			while (first < tail)
			{
				ranges::iter_swap(first, tail);
				++first;
				--tail;
			}
		}

		return i;
	}

	template <typename Iter, typename Sent>
	static BKSGE_CXX14_CONSTEXPR Iter
	impl(Iter first, Sent last,
		bksge::detail::overload_priority<0>)
	{
		auto i = ranges::next(first, last);
		auto tail = i;

		for (;;)
		{
			if (first == tail || first == --tail)
			{
				break;
			}
			else
			{
				ranges::iter_swap(first, tail);
				++first;
			}
		}

		return i;
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::bidirectional_iterator Iter,
		bksge::sentinel_for<Iter> Sent
	>
	requires bksge::permutable<Iter>
#else
	template <
		typename Iter,
		typename Sent,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::bidirectional_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::permutable<Iter>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(Iter first, Sent last) const
	{
		return impl(
			bksge::move(first),
			bksge::move(last),
			bksge::detail::overload_priority<1>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::bidirectional_range Range>
	requires bksge::permutable<ranges::iterator_t<Range>>
#else
	template <
		typename Range,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::bidirectional_range<Range>,
			bksge::permutable<ranges::iterator_t<Range>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r) const
	{
		return (*this)(ranges::begin(r), ranges::end(r));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR reverse_fn reverse{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REVERSE_HPP
