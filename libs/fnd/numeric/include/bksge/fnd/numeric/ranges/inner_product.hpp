/**
 *	@file	inner_product.hpp
 *
 *	@brief	ranges::inner_product の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_RANGES_INNER_PRODUCT_HPP
#define BKSGE_FND_NUMERIC_RANGES_INNER_PRODUCT_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/indirect_result_t.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/unreachable_sentinel.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct inner_product_fn
{
	template <
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Iter1),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter1, Sent1),
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Iter2),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter2, Sent2),
		typename T,
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F1, bksge::plus<>),
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F2, bksge::multiplies<>),
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::assignable_from<T&,
		bksge::invoke_result_t<F1&,
			T,
			bksge::indirect_result_t<F2&,
				bksge::projected<Iter1, Proj1>,
				bksge::projected<Iter2, Proj2>>>>
#else
		, typename = bksge::enable_if_t<
			bksge::assignable_from<T&,
				bksge::invoke_result_t<F1&,
					T,
					bksge::indirect_result_t<F2&,
						bksge::projected<Iter1, Proj1>,
						bksge::projected<Iter2, Proj2>>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR T
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		T init,
		F1 binary_op1 = {},
		F2 binary_op2 = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		while (first1 != last1 && first2 != last2)
		{
			init = bksge::invoke(binary_op1, init,
				bksge::invoke(binary_op2,
					bksge::invoke(proj1, *first1),
					bksge::invoke(proj2, *first2)));
			++first1;
			++first2;
		}

		return init;
	}

	template <
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Iter1),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter1, Sent1),
		BKSGE_REQUIRES_PARAM(bksge::input_iterator, Iter2),
		typename T,
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F1, bksge::plus<>),
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F2, bksge::multiplies<>),
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::assignable_from<T&,
		bksge::invoke_result_t<F1&,
			T,
			bksge::indirect_result_t<F2&,
				bksge::projected<Iter1, Proj1>,
				bksge::projected<Iter2, Proj2>>>>
#else
		, typename = bksge::enable_if_t<
			bksge::assignable_from<T&,
				bksge::invoke_result_t<F1&,
					T,
					bksge::indirect_result_t<F2&,
						bksge::projected<Iter1, Proj1>,
						bksge::projected<Iter2, Proj2>>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR T
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2,
		T init,
		F1 binary_op1 = {},
		F2 binary_op2 = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			std::move(first1),
			std::move(last1),
			std::move(first2),
			bksge::unreachable_sentinel,
			std::move(init),
			std::move(binary_op1),
			std::move(binary_op2),
			std::move(proj1),
			std::move(proj2));
	}

	template <
		BKSGE_REQUIRES_PARAM(ranges::input_range, Range1),
		BKSGE_REQUIRES_PARAM(ranges::input_range, Range2),
		typename T,
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F1, bksge::plus<>),
		BKSGE_REQUIRES_PARAM_D(bksge::copy_constructible, F2, bksge::multiplies<>),
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::assignable_from<T&,
		bksge::invoke_result_t<F1&,
			T,
			bksge::indirect_result_t<F2&,
				bksge::projected<ranges::iterator_t<Range1>, Proj1>,
				bksge::projected<ranges::iterator_t<Range2>, Proj2>>>>
#else
		, typename = bksge::enable_if_t<
			bksge::assignable_from<T&,
				bksge::invoke_result_t<F1&,
					T,
					bksge::indirect_result_t<F2&,
						bksge::projected<ranges::iterator_t<Range1>, Proj1>,
						bksge::projected<ranges::iterator_t<Range2>, Proj2>>>>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR T
	operator()(
		Range1&& r1,
		Range2&& r2,
		T init,
		F1 binary_op1 = {},
		F2 binary_op2 = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			std::move(init),
			std::move(binary_op1),
			std::move(binary_op2),
			std::move(proj1),
			std::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR inner_product_fn inner_product{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_RANGES_INNER_PRODUCT_HPP
