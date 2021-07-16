/**
 *	@file	adjacent_difference.hpp
 *
 *	@brief	ranges::adjacent_difference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_RANGES_ADJACENT_DIFFERENCE_HPP
#define BKSGE_FND_NUMERIC_RANGES_ADJACENT_DIFFERENCE_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/functional/minus.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/iterator/indirect_result_t.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
using adjacent_difference_result = in_out_result<Iter, Out>;

struct adjacent_difference_fn
{
	template <
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Iter),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter, Sent),
		BKSGE_REQUIRES_PARAM(bksge::weakly_incrementable, Out),
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F, bksge::minus<>),
		typename Proj = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::indirectly_writable<Out,
		bksge::indirect_result_t<F&,
			bksge::projected<Iter, Proj>,
			bksge::projected<Iter, Proj>>>
#else
		, typename = bksge::enable_if_t<
			bksge::indirectly_writable<Out,
				bksge::indirect_result_t<F&,
					bksge::projected<Iter, Proj>,
					bksge::projected<Iter, Proj>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	adjacent_difference_result<Iter, Out>
	operator()(Iter first, Sent last, Out result, F binary_op = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return { std::move(first), std::move(result) };
		}

		auto acc = bksge::invoke(proj, *first);
		*result = acc;
		++result;
		++first;

		while (first != last)
		{
			auto val = bksge::invoke(proj, *first);
			*result = bksge::invoke(binary_op, val, acc);
			acc = std::move(val);

			++result;
			++first;
		}

		return { std::move(first), std::move(result) };
	}

	template <
		BKSGE_REQUIRES_PARAM(ranges::input_range, Range),
		BKSGE_REQUIRES_PARAM(bksge::weakly_incrementable, Out),
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F, bksge::minus<>),
		typename Proj = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::indirectly_writable<Out,
		bksge::indirect_result_t<F&,
			bksge::projected<ranges::iterator_t<Range>, Proj>,
			bksge::projected<ranges::iterator_t<Range>, Proj>>>
#else
		, typename = bksge::enable_if_t<
			bksge::indirectly_writable<Out,
				bksge::indirect_result_t<F&,
					bksge::projected<ranges::iterator_t<Range>, Proj>,
					bksge::projected<ranges::iterator_t<Range>, Proj>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	adjacent_difference_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result, F binary_op = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(result),
			std::move(binary_op),
			std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR adjacent_difference_fn adjacent_difference{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_RANGES_ADJACENT_DIFFERENCE_HPP
