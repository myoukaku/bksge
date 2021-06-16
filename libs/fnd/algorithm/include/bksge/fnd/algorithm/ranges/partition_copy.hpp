/**
 *	@file	partition_copy.hpp
 *
 *	@brief	ranges::partition_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_PARTITION_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_PARTITION_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_out_result.hpp>
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
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out1, typename Out2>
using partition_copy_result = in_out_out_result<Iter, Out1, Out2>;

struct partition_copy_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out1,
		bksge::weakly_incrementable Out2,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<Iter, Proj>
		> Pred
	>
	requires
		bksge::indirectly_copyable<Iter, Out1> &&
		bksge::indirectly_copyable<Iter, Out2>
#else
	template <
		typename Iter, typename Sent, typename Out1, typename Out2,
		typename Proj = bksge::identity, typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out1>,
			bksge::weakly_incrementable<Out2>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<Iter, Proj>>,
			bksge::indirectly_copyable<Iter, Out1>,
			bksge::indirectly_copyable<Iter, Out2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR partition_copy_result<Iter, Out1, Out2>
	operator()(
		Iter first, Sent last,
		Out1 out_true, Out2 out_false,
		Pred pred, Proj proj = {}) const
	{
		for (; first != last; ++first)
		{
			if (bksge::invoke(pred, bksge::invoke(proj, *first)))
			{
				*out_true = *first;
				++out_true;
			}
			else
			{
				*out_false = *first;
				++out_false;
			}
		}

		return { bksge::move(first), bksge::move(out_true), bksge::move(out_false) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		bksge::weakly_incrementable Out1,
		bksge::weakly_incrementable Out2,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Pred
	>
	requires
		bksge::indirectly_copyable<ranges::iterator_t<Range>, Out1> &&
		bksge::indirectly_copyable<ranges::iterator_t<Range>, Out2>
#else
	template <
		typename Range, typename Out1, typename Out2,
		typename Proj = bksge::identity, typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::weakly_incrementable<Out1>,
			bksge::weakly_incrementable<Out2>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<ranges::iterator_t<Range>, Proj>>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out1>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	partition_copy_result<ranges::borrowed_iterator_t<Range>, Out1, Out2>
	operator()(
		Range&& r, Out1 out_true, Out2 out_false,
		Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(out_true), bksge::move(out_false),
			bksge::move(pred), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR partition_copy_fn partition_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_PARTITION_COPY_HPP
