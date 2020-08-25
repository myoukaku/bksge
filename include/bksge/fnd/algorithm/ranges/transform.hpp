/**
 *	@file	transform.hpp
 *
 *	@brief	ranges::transform の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_TRANSFORM_HPP
#define BKSGE_FND_ALGORITHM_RANGES_TRANSFORM_HPP

#include <bksge/fnd/algorithm/ranges/in_out_result.hpp>
#include <bksge/fnd/algorithm/ranges/in_in_out_result.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/iterator/indirect_result_t.hpp>
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
using unary_transform_result = in_out_result<Iter, Out>;

template <typename Iter1, typename Iter2, typename Out>
using binary_transform_result = in_in_out_result<Iter1, Iter2, Out>;

struct transform_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		bksge::weakly_incrementable Out,
		bksge::copy_constructible F,
		typename Proj = bksge::identity
	>
	requires bksge::indirectly_writable<Out,
		bksge::indirect_result_t<F&,
			bksge::projected<Iter, Proj>>>
#else
	template <
		typename Iter,
		typename Sent,
		typename Out,
		typename F,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::weakly_incrementable<Out>,
			bksge::copy_constructible<F>,
			bksge::indirectly_writable<Out,
				bksge::indirect_result_t<F&,
					bksge::projected<Iter, Proj>>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR unary_transform_result<Iter, Out>
	operator()(
		Iter first1, Sent last1, Out result, F op, Proj proj = {}) const
	{
		for (; first1 != last1; ++first1, (void)++result)
		{
			*result = bksge::invoke(op, bksge::invoke(proj, *first1));
		}

		return { bksge::move(first1), bksge::move(result) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		bksge::weakly_incrementable Out,
		bksge::copy_constructible F,
		typename Proj = bksge::identity
	>
	requires bksge::indirectly_writable<Out,
		bksge::indirect_result_t<F&,
			bksge::projected<ranges::iterator_t<Range>, Proj>>>
#else
	template <
		typename Range,
		typename Out,
		typename F,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::weakly_incrementable<Out>,
			bksge::copy_constructible<F>,
			bksge::indirectly_writable<Out,
				bksge::indirect_result_t<F&,
					bksge::projected<ranges::iterator_t<Range>, Proj>>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR unary_transform_result<ranges::borrowed_iterator_t<Range>, Out>
	operator()(Range&& r, Out result, F op, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(result),
			bksge::move(op),
			bksge::move(proj));
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		bksge::weakly_incrementable Out,
		bksge::copy_constructible F,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_writable<Out,
		bksge::indirect_result_t<F&,
			bksge::projected<Iter1, Proj1>,
			bksge::projected<Iter2, Proj2>>>
#else
	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Out,
		typename F,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::weakly_incrementable<Out>,
			bksge::copy_constructible<F>,
			bksge::indirectly_writable<Out,
				bksge::indirect_result_t<F&,
					bksge::projected<Iter1, Proj1>,
					bksge::projected<Iter2, Proj2>>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR binary_transform_result<Iter1, Iter2, Out>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Out result, F binary_op,
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	{
		for (; first1 != last1 && first2 != last2;
			++first1, (void)++first2, ++result)
		{
			*result = bksge::invoke(binary_op,
				bksge::invoke(proj1, *first1),
				bksge::invoke(proj2, *first2));
		}

		return { bksge::move(first1), bksge::move(first2), bksge::move(result) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range1,
		ranges::input_range Range2,
		bksge::weakly_incrementable Out,
		bksge::copy_constructible F,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_writable<Out,
		bksge::indirect_result_t<F&,
			bksge::projected<ranges::iterator_t<Range1>, Proj1>,
			bksge::projected<ranges::iterator_t<Range2>, Proj2>>>
#else
	template <
		typename Range1,
		typename Range2,
		typename Out,
		typename F,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::input_range<Range2>,
			bksge::weakly_incrementable<Out>,
			bksge::copy_constructible<F>,
			bksge::indirectly_writable<Out,
				bksge::indirect_result_t<F&,
					bksge::projected<ranges::iterator_t<Range1>, Proj1>,
					bksge::projected<ranges::iterator_t<Range2>, Proj2>>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR binary_transform_result<
		ranges::borrowed_iterator_t<Range1>,
		ranges::borrowed_iterator_t<Range2>,
		Out
	>
	operator()(
		Range1&& r1, Range2&& r2, Out result, F binary_op,
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			bksge::move(result), bksge::move(binary_op),
			bksge::move(proj1), bksge::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR transform_fn transform{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_TRANSFORM_HPP
