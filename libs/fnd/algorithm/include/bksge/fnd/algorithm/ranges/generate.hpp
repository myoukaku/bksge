/**
 *	@file	generate.hpp
 *
 *	@brief	ranges::generate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_GENERATE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_GENERATE_HPP

#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/ranges/concepts/output_range.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct generate_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_or_output_iterator Out,
		bksge::sentinel_for<Out> Sent,
		bksge::copy_constructible F
	>
	requires bksge::invocable<F&> &&
		bksge::indirectly_writable<Out, bksge::invoke_result_t<F&>>
#else
	template <
		typename Out, typename Sent, typename F,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_or_output_iterator<Out>,
			bksge::sentinel_for<Sent, Out>,
			bksge::copy_constructible<F>,
			bksge::invocable<F&>,
			bksge::indirectly_writable<Out, bksge::invoke_result_t<F&>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Out operator()(
		Out first, Sent last, F gen) const
	{
		for (; first != last; ++first)
		{
			*first = bksge::invoke(gen);
		}
		return first;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Range, bksge::copy_constructible F>
	requires bksge::invocable<F&> &&
		ranges::output_range<Range, bksge::invoke_result_t<F&>>
#else
	template <
		typename Range, typename F,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::copy_constructible<F>,
			bksge::invocable<F&>,
			ranges::output_range<Range, bksge::invoke_result_t<F&>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, F gen) const
	{
		return (*this)(ranges::begin(r), ranges::end(r), std::move(gen));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR generate_fn generate{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_GENERATE_HPP
