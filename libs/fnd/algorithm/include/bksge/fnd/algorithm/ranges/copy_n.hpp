/**
 *	@file	copy_n.hpp
 *
 *	@brief	ranges::copy_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_COPY_N_HPP
#define BKSGE_FND_ALGORITHM_RANGES_COPY_N_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_copyable.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
using copy_n_result = in_out_result<Iter, Out>;

struct copy_n_fn
{
private:
	template <
		BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iter),
		typename Difference, typename Out
	>
	static BKSGE_CXX14_CONSTEXPR copy_n_result<Iter, Out>
	impl(Iter first, Difference n, Out result,
		bksge::detail::overload_priority<1>)
	{
		if (n > 0)
		{
			return ranges::copy(first, first + n, bksge::move(result));
		}

		return { bksge::move(first), bksge::move(result) };
	}

	template <typename Iter, typename Difference, typename Out>
	static BKSGE_CXX14_CONSTEXPR copy_n_result<Iter, Out>
	impl(Iter first, Difference n, Out result,
		bksge::detail::overload_priority<0>)
	{
		for (; n > 0; --n, (void)++result, (void)++first)
		{
			*result = *first;
		}

		return { bksge::move(first), bksge::move(result) };
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::weakly_incrementable Out
	>
	requires bksge::indirectly_copyable<Iter, Out>
#else
	template <
		typename Iter,
		typename Out,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::indirectly_copyable<Iter, Out>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR copy_n_result<Iter, Out>
	operator()(Iter first, bksge::iter_difference_t<Iter> n, Out result) const
	{
		return impl(
			bksge::move(first),
			bksge::move(n),
			bksge::move(result),
			bksge::detail::overload_priority<1>{});
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR copy_n_fn copy_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_COPY_N_HPP
