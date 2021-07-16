/**
 *	@file	copy_if.hpp
 *
 *	@brief	ranges::copy_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_COPY_IF_HPP
#define BKSGE_FND_ALGORITHM_RANGES_COPY_IF_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
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

template <typename Iter, typename Out>
using copy_if_result = in_out_result<Iter, Out>;

struct copy_if_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<Iter, Proj>
		> Pred
	>
	requires bksge::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirect_unary_predicate<
				Pred,
				bksge::projected<Iter, Proj>
			>,
			bksge::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR copy_if_result<Iter, Out>
	operator()(
		Iter first, Sent last, Out result, Pred pred, Proj proj = {}) const
	{
		for (; first != last; ++first)
		{
			if (bksge::invoke(pred, bksge::invoke(proj, *first)))
			{
				*result = *first;
				++result;
			}
		}

		return { std::move(first), std::move(result) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		bksge::weakly_incrementable Out,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Pred
	>
	requires bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
#else
	template <
		typename Range,
		typename Out,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::indirect_unary_predicate<
				Pred,
				bksge::projected<ranges::iterator_t<Range>, Proj>
			>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	copy_if_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(
		Range&& r, Out result, Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result),
			std::move(pred),
			std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR copy_if_fn copy_if{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_COPY_IF_HPP
