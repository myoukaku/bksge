/**
 *	@file	replace_copy.hpp
 *
 *	@brief	ranges::replace_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REPLACE_COPY_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REPLACE_COPY_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/output_iterator.hpp>
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
using replace_copy_result = in_out_result<Iter, Out>;

struct replace_copy_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T1,
		typename T2,
		bksge::output_iterator<T2 const&> Out,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirectly_copyable<Iter, Out> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<Iter, Proj>,
			T1 const*>
#else
	template <
		typename Iter,
		typename Sent,
		typename T1,
		typename T2,
		typename Out,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::output_iterator<Out, T2 const&>,
			bksge::indirectly_copyable<Iter, Out>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<Iter, Proj>,
				T1 const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR replace_copy_result<Iter, Out>
	operator()(
		Iter first, Sent last,
		Out result,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		for (; first != last; ++first, (void)++result)
		{
			if (bksge::invoke(proj, *first) == old_value)
			{
				*result = new_value;
			}
			else
			{
				*result = *first;
			}
		}

		return { bksge::move(first), bksge::move(result) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		typename T1,
		typename T2,
		bksge::output_iterator<T2 const&> Out,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirectly_copyable<ranges::iterator_t<Range>, Out> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<ranges::iterator_t<Range>, Proj>,
			T1 const*>
#else
	template <
		typename Range,
		typename T1,
		typename T2,
		typename Out,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::output_iterator<Out, T2 const&>,
			bksge::indirectly_copyable<ranges::iterator_t<Range>, Out>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<ranges::iterator_t<Range>, Proj>,
				T1 const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	replace_copy_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(
		Range&& r,
		Out result,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(result),
			old_value,
			new_value,
			bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR replace_copy_fn replace_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REPLACE_COPY_HPP
