/**
 *	@file	rotate_copy.hpp
 *
 *	@brief	ranges::rotate_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_ROTATE_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_ROTATE_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
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

template <typename Iter, typename Out>
using rotate_copy_result = in_out_result<Iter, Out>;

struct rotate_copy_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::forward_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR rotate_copy_result<Iter, Out>
	operator()(Iter first, Iter middle, Sent last, Out result) const
	{
		auto copy1 = ranges::copy(
			middle,
			bksge::move(last),
			bksge::move(result));
		auto copy2 = ranges::copy(
			bksge::move(first),
			bksge::move(middle),
			bksge::move(copy1.out));
		return { bksge::move(copy1.in), bksge::move(copy2.out) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::forward_range Range,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
#else
	template <
		typename Range,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	rotate_copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, ranges::iterator_t<Range> middle, Out result) const
	{
		return (*this)(
			ranges::begin(r),
			bksge::move(middle),
			ranges::end(r),
			bksge::move(result));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR rotate_copy_fn rotate_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_ROTATE_COPY_HPP
