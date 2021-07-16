/**
 *	@file	reverse_copy.hpp
 *
 *	@brief	ranges::reverse_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REVERSE_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REVERSE_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
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
using reverse_copy_result = in_out_result<Iter, Out>;

struct reverse_copy_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::bidirectional_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter, typename Sent, typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::bidirectional_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	reverse_copy_result<Iter, Out>
	operator()(Iter first, Sent last, Out result) const
	{
		auto i = ranges::next(first, last);
		auto tail = i;
		while (first != tail)
		{
			--tail;
			*result = *tail;
			++result;
		}

		return { i, result };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::bidirectional_range Range,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
#else
	template <
		typename Range, typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::bidirectional_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	reverse_copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR reverse_copy_fn reverse_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REVERSE_COPY_HPP
