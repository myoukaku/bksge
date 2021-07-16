/**
 *	@file	shuffle.hpp
 *
 *	@brief	ranges::shuffle の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_SHUFFLE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_SHUFFLE_HPP

#include <bksge/fnd/algorithm/shuffle.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/permutable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/random/concepts/uniform_random_bit_generator.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct shuffle_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::random_access_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Gen
	>
	requires bksge::permutable<Iter> &&
		bksge::uniform_random_bit_generator<bksge::remove_reference_t<Gen>>
#else
	template <
		typename Iter, typename Sent, typename Gen,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::random_access_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::permutable<Iter>,
			bksge::uniform_random_bit_generator<bksge::remove_reference_t<Gen>>
		>::value>
	>
#endif
	Iter operator()(Iter first, Sent last, Gen&& g) const
	{
		auto lasti = ranges::next(first, last);
		bksge::shuffle(std::move(first), lasti, bksge::forward<Gen>(g));
		return lasti;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::random_access_range Range, typename Gen>
	requires bksge::permutable<ranges::iterator_t<Range>> &&
		bksge::uniform_random_bit_generator<bksge::remove_reference_t<Gen>>
#else
	template <
		typename Range, typename Gen,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::random_access_range<Range>,
			bksge::permutable<ranges::iterator_t<Range>>,
			bksge::uniform_random_bit_generator<bksge::remove_reference_t<Gen>>
		>::value>
	>
#endif
	ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Gen&& g) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r), bksge::forward<Gen>(g));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR shuffle_fn shuffle{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_SHUFFLE_HPP
