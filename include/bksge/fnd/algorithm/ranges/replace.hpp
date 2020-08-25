/**
 *	@file	replace.hpp
 *
 *	@brief	ranges::replace の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_REPLACE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_REPLACE_HPP

#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
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

struct replace_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T1,
		typename T2,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirectly_writable<Iter, T2 const&> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to, bksge::projected<Iter, Proj>, T1 const*>
#else
	template <
		typename Iter,
		typename Sent,
		typename T1,
		typename T2,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirectly_writable<Iter, T2 const&>,
			bksge::indirect_binary_predicate<
				ranges::equal_to, bksge::projected<Iter, Proj>, T1 const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(
		Iter first, Sent last,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		for (; first != last; ++first)
		{
			if (bksge::invoke(proj, *first) == old_value)
			{
				*first = new_value;
			}
		}

		return first;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		typename T1,
		typename T2,
		typename Proj = bksge::identity
	>
	requires
		bksge::indirectly_writable<ranges::iterator_t<Range>, T2 const&> &&
		bksge::indirect_binary_predicate<
			ranges::equal_to,
			bksge::projected<ranges::iterator_t<Range>, Proj>,
			T1 const*>
#else
	template <
		typename Range,
		typename T1,
		typename T2,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::indirectly_writable<ranges::iterator_t<Range>, T2 const&>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<ranges::iterator_t<Range>, Proj>,
				T1 const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(
		Range&& r,
		T1 const& old_value,
		T2 const& new_value,
		Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			old_value, new_value, bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR replace_fn replace{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_REPLACE_HPP
