/**
 *	@file	generate_n.hpp
 *
 *	@brief	ranges::generate_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_GENERATE_N_HPP
#define BKSGE_FND_ALGORITHM_RANGES_GENERATE_N_HPP

#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct generate_n_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_or_output_iterator Out,
		bksge::copy_constructible F
	>
	requires bksge::invocable<F&> &&
		bksge::indirectly_writable<Out, bksge::invoke_result_t<F&>>
#else
	template <
		typename Out,
		typename F,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_or_output_iterator<Out>,
			bksge::copy_constructible<F>,
			bksge::invocable<F&>,
			bksge::indirectly_writable<Out, bksge::invoke_result_t<F&>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Out operator()(
		Out first, bksge::iter_difference_t<Out> n, F gen) const
	{
		for (; n > 0; --n, (void)++first)
		{
			*first = bksge::invoke(gen);
		}

		return first;
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR generate_n_fn generate_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_GENERATE_N_HPP
