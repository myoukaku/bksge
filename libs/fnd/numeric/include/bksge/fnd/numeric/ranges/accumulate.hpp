/**
 *	@file	accumulate.hpp
 *
 *	@brief	ranges::accumulate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_RANGES_ACCUMULATE_HPP
#define BKSGE_FND_NUMERIC_RANGES_ACCUMULATE_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
//#include <bksge/fnd/functional/ranges/plus.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/indirect_result_t.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct accumulate_fn
{
	template <
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Iter),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter, Sent),
		typename T,
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F, bksge::plus<>),
		typename Proj = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::assignable_from<T&,
		bksge::indirect_result_t<F&,
			T*, bksge::projected<Iter, Proj>>>
#else
		, typename = bksge::enable_if_t<
			bksge::assignable_from<T&,
				bksge::indirect_result_t<F&,
					T*, bksge::projected<Iter, Proj>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR T operator()(
		Iter first, Sent last, T init, F binary_op = {}, Proj proj = {}) const
	{
		for(; first != last; ++first)
		{
			init = bksge::invoke(binary_op, init, bksge::invoke(proj, *first));
		}
		return init;
	}

	template <
		BKSGE_REQUIRES_PARAM(ranges::input_range, Range),
		typename T,
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F, bksge::plus<>),
		typename Proj = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::assignable_from<T&,
		bksge::indirect_result_t<F&,
			T*, bksge::projected<ranges::iterator_t<Range>, Proj>>>
#else
		, typename = bksge::enable_if_t<
			bksge::assignable_from<T&,
				bksge::indirect_result_t<F&,
					T*, bksge::projected<ranges::iterator_t<Range>, Proj>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR T
	operator()(Range&& r, T init, F binary_op = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(init),
			bksge::move(binary_op),
			bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR accumulate_fn accumulate{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_RANGES_ACCUMULATE_HPP
