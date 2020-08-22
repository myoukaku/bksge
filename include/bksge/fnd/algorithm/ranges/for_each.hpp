/**
 *	@file	for_each.hpp
 *
 *	@brief	ranges::for_each の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_FOR_EACH_HPP
#define BKSGE_FND_ALGORITHM_RANGES_FOR_EACH_HPP

#include <bksge/fnd/algorithm/ranges/in_fun_result.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_unary_invocable.hpp>
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

template <typename Iter, typename F>
using for_each_result = in_fun_result<Iter, F>;

struct for_each_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirectly_unary_invocable<bksge::projected<Iter, Proj>> Fun
#else
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Fun,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirectly_unary_invocable<Fun, bksge::projected<Iter, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR for_each_result<Iter, Fun>
	operator()(Iter first, Sent last, Fun f, Proj proj ={}) const
	{
		for (; first != last; ++first)
		{
			bksge::invoke(f, bksge::invoke(proj, *first));
		}

		return { bksge::move(first), bksge::move(f) };
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::input_range Range,
		typename Proj = bksge::identity,
		bksge::indirectly_unary_invocable<bksge::projected<ranges::iterator_t<Range>, Proj>> Fun
#else
		typename Range,
		typename Proj = bksge::identity,
		typename Fun,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::indirectly_unary_invocable<Fun, bksge::projected<ranges::iterator_t<Range>, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR for_each_result<ranges::borrowed_iterator_t<Range>, Fun>
	operator()(Range&& r, Fun f, Proj proj ={}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(f), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR for_each_fn for_each{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_FOR_EACH_HPP
