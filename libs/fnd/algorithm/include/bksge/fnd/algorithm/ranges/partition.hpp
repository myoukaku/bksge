/**
 *	@file	partition.hpp
 *
 *	@brief	ranges::partition の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_PARTITION_HPP
#define BKSGE_FND_ALGORITHM_RANGES_PARTITION_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct partition_fn
{
private:
	template <
		BKSGE_REQUIRES_PARAM(bksge::bidirectional_iterator, Iter),
		typename Sent,
		typename Proj,
		typename Pred
	>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Pred pred, Proj proj,
		bksge::detail::overload_priority<1>)
	{
		auto lasti = ranges::next(first, last);
		auto tail = lasti;
		for (;;)
		{
			for (;;)
			{
				if (first == tail)
				{
					return { std::move(first), std::move(lasti) };
				}
				else if (bksge::invoke(pred, bksge::invoke(proj, *first)))
				{
					++first;
				}
				else
				{
					break;
				}
			}

			--tail;

			for (;;)
			{
				if (first == tail)
				{
					return { std::move(first), std::move(lasti) };
				}
				else if (!(bool)bksge::invoke(pred, bksge::invoke(proj, *tail)))
				{
					--tail;
				}
				else
				{
					break;
				}
			}

			ranges::iter_swap(first, tail);
			++first;
		}
	}

	template <
		typename Iter,
		typename Sent,
		typename Proj,
		typename Pred
	>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Pred pred, Proj proj,
		bksge::detail::overload_priority<0>)
	{
		if (first == last)
		{
			return { std::move(first), std::move(first) };
		}

		while (bksge::invoke(pred, bksge::invoke(proj, *first)))
		{
			if (++first == last)
			{
				return { std::move(first), std::move(first) };
			}
		}

		auto next_it = first;
		while (++next_it != last)
		{
			if (bksge::invoke(pred, bksge::invoke(proj, *next_it)))
			{
				ranges::iter_swap(first, next_it);
				++first;
			}
		}

		return { std::move(first), std::move(next_it) };
	}

public:
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::permutable Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<Iter, Proj>
		> Pred
#else
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::permutable<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<Iter, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(
		Iter first, Sent last,
		Pred pred, Proj proj = {}) const
	{
		return impl(
			std::move(first),
			std::move(last),
			std::move(pred),
			std::move(proj),
			bksge::detail::overload_priority<1>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::forward_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Pred
	>
	requires bksge::permutable<ranges::iterator_t<Range>>
#else
	template <
		typename Range,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<ranges::iterator_t<Range>, Proj>>,
			bksge::permutable<ranges::iterator_t<Range>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range>
	operator()(Range&& r, Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR partition_fn partition{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_PARTITION_HPP
