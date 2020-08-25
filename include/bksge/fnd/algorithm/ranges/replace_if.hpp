/**
 *	@file	replace_if.hpp
 *
 *	@brief	ranges::replace_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REPLACE_IF_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REPLACE_IF_HPP

#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
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

struct replace_if_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<bksge::projected<Iter, Proj>> Pred
	>
	requires bksge::indirectly_writable<Iter, T const&>
#else
	template <
		typename Iter,
		typename Sent,
		typename T,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_unary_predicate<Pred, bksge::projected<Iter, Proj>>,
			bksge::indirectly_writable<Iter, T const&>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last,
		Pred pred, T const& new_value, Proj proj = {}) const
	{
		for (; first != last; ++first)
		{
			if (bksge::invoke(pred, bksge::invoke(proj, *first)))
			{
				*first = new_value;
			}
		}

		return bksge::move(first);
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		typename T,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Pred
	>
	requires bksge::indirectly_writable<ranges::iterator_t<Range>, T const&>
#else
	template <
		typename Range,
		typename T,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<ranges::iterator_t<Range>, Proj>>,
			bksge::indirectly_writable<ranges::iterator_t<Range>, T const&>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Pred pred, T const& new_value, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(pred), new_value, bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR replace_if_fn replace_if{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REPLACE_IF_HPP
