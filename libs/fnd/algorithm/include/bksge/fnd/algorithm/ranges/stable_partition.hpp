/**
 *	@file	stable_partition.hpp
 *
 *	@brief	ranges::stable_partition の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_STABLE_PARTITION_HPP
#define BKSGE_FND_ALGORITHM_RANGES_STABLE_PARTITION_HPP

#include <bksge/fnd/algorithm/stable_partition.hpp>
#include <bksge/fnd/algorithm/ranges/detail/make_pred_proj.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
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

struct stable_partition_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::bidirectional_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<Iter, Proj>
		> Pred
	>
	requires bksge::permutable<Iter>
#else
	template <
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::bidirectional_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<Iter, Proj>>, 
			bksge::permutable<Iter>
		>::value>
	>
#endif
	ranges::subrange<Iter> operator()(
		Iter first, Sent last,
		Pred pred, Proj proj = {}) const
	{
		auto lasti = ranges::next(first, last);
		auto middle = bksge::stable_partition(
			std::move(first), lasti, detail::make_pred_proj(pred, proj));
		return { std::move(middle), std::move(lasti) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::bidirectional_range Range,
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
			ranges::bidirectional_range<Range>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<ranges::iterator_t<Range>, Proj>>,
			bksge::permutable<ranges::iterator_t<Range>>
		>::value>
	>
#endif
	ranges::borrowed_subrange_t<Range>
	operator()(Range&& r, Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR stable_partition_fn stable_partition{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_STABLE_PARTITION_HPP
