/**
 *	@file	remove_if.hpp
 *
 *	@brief	ranges::remove_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REMOVE_IF_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REMOVE_IF_HPP

#include <bksge/fnd/algorithm/ranges/find_if.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
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

struct remove_if_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::permutable Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<Iter, Proj>
		> Pred
	>
#else
	template <
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::permutable<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<Iter, Proj>
			>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(
		Iter first, Sent last, Pred pred, Proj proj = {}) const
	{
		first = ranges::find_if(first, last, pred, proj);
		if (first == last)
		{
			return { first, first };
		}

		auto result = first;
		++first;
		for (; first != last; ++first)
		{
			if (!bksge::invoke(pred, bksge::invoke(proj, *first)))
			{
				*result = std::move(*first);
				++result;
			}
		}

		return { result, first };
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

BKSGE_INLINE_VAR BKSGE_CONSTEXPR remove_if_fn remove_if{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REMOVE_IF_HPP
