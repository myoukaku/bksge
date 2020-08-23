/**
 *	@file	for_each_n.hpp
 *
 *	@brief	ranges::for_each_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_FOR_EACH_N_HPP
#define BKSGE_FND_ALGORITHM_RANGES_FOR_EACH_N_HPP

#include <bksge/fnd/algorithm/ranges/in_fun_result.hpp>
#include <bksge/fnd/algorithm/ranges/for_each.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_unary_invocable.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename F>
using for_each_n_result = in_fun_result<Iter, F>;

struct for_each_n_fn
{
private:
	template <
		BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iter),
		typename Difference,
		typename Proj,
		typename Fun
	>
	static BKSGE_CXX14_CONSTEXPR for_each_n_result<Iter, Fun>
	impl(Iter first, Difference n, Fun f, Proj proj, bksge::detail::overload_priority<1>)
	{
		if (n <= 0)
		{
			return { bksge::move(first), bksge::move(f) };
		}

		auto last = first + n;
		return ranges::for_each(
			bksge::move(first), bksge::move(last),
			bksge::move(f), bksge::move(proj));
	}

	template <
		typename Iter,
		typename Difference,
		typename Proj,
		typename Fun
	>
	static BKSGE_CXX14_CONSTEXPR for_each_n_result<Iter, Fun>
	impl(Iter first, Difference n, Fun f, Proj proj, bksge::detail::overload_priority<0>)
	{
		while (n-- > 0)
		{
			bksge::invoke(f, bksge::invoke(proj, *first));
			++first;
		}

		return { bksge::move(first), bksge::move(f) };
	}

public:
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::input_iterator Iter,
		typename Proj = bksge::identity,
		bksge::indirectly_unary_invocable<bksge::projected<Iter, Proj>> Fun
#else
		typename Iter,
		typename Proj = bksge::identity,
		typename Fun,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::indirectly_unary_invocable<Fun, bksge::projected<Iter, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR for_each_n_result<Iter, Fun>
	operator()(
		Iter first, bksge::iter_difference_t<Iter> n,
		Fun f, Proj proj = {}) const
	{
		return impl(first, n, f, proj, bksge::detail::overload_priority<1>{});
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR for_each_n_fn for_each_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_FOR_EACH_N_HPP
