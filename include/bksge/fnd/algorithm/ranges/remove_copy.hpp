/**
 *	@file	remove_copy.hpp
 *
 *	@brief	ranges::remove_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REMOVE_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REMOVE_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/concepts/indirect_binary_predicate.hpp>
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

template <typename Iter, typename Out>
using remove_copy_result = in_out_result<Iter, Out>;

struct remove_copy_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out,
		typename T,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirectly_copyable<Iter, Out> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<Iter, Proj>,
			T const*>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename T,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<Iter, Out>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<Iter, Proj>,
				T const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	remove_copy_result<Iter, Out>
	operator()(
		Iter first, Sent last, Out result,
		T const& value, Proj proj = {}) const
	{
		for (; first != last; ++first)
		{
			if (!(bksge::invoke(proj, *first) == value))
			{
				*result = *first;
				++result;
			}
		}

		return { bksge::move(first), bksge::move(result) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		bksge::weakly_incrementable Out,
		typename T,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirectly_copyable<ranges::iterator_t<Range>, Out> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<ranges::iterator_t<Range>, Proj>,
			T const*>
#else
	template <
		typename Range,
		typename Out,
		typename T,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<ranges::iterator_t<Range>, Proj>,
				T const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	remove_copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(
		Range&& r, Out result,
		T const& value, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(result), value, bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR remove_copy_fn remove_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REMOVE_COPY_HPP
