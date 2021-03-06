﻿/**
 *	@file	random_access_iterator.hpp
 *
 *	@brief	random_access_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_concept.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/totally_ordered.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept random_access_iterator =
	bksge::bidirectional_iterator<Iter> &&
	bksge::derived_from<bksge::detail::iter_concept<Iter>, bksge::random_access_iterator_tag> &&
	bksge::totally_ordered<Iter> &&
	bksge::sized_sentinel_for<Iter, Iter> &&
	requires(Iter i, Iter const j, bksge::iter_difference_t<Iter> const n)
	{
		{ i += n } -> bksge::same_as<Iter&>;
		{ j +  n } -> bksge::same_as<Iter>;
		{ n +  j } -> bksge::same_as<Iter>;
		{ i -= n } -> bksge::same_as<Iter&>;
		{ j -  n } -> bksge::same_as<Iter>;
		{  j[n]  } -> bksge::same_as<bksge::iter_reference_t<Iter>>;
	};

template <typename Iter>
using is_random_access_iterator = bksge::bool_constant<random_access_iterator<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct random_access_iterator_impl
{
private:
	template <typename I2,
		typename = bksge::enable_if_t<bksge::bidirectional_iterator<I2>::value>,
		typename = bksge::enable_if_t<bksge::derived_from<
			bksge::detail::iter_concept<I2>, bksge::random_access_iterator_tag>::value>,
		typename = bksge::enable_if_t<bksge::totally_ordered<I2>::value>,
		typename = bksge::enable_if_t<bksge::sized_sentinel_for<I2, I2>::value>,
		typename J2 = I2 const,
		typename D = bksge::iter_difference_t<I2> const,
		typename T1 = decltype(bksge::declval<I2&>() += bksge::declval<D >()),
		typename T2 = decltype(bksge::declval<J2 >() +  bksge::declval<D >()),
		typename T3 = decltype(bksge::declval<D  >() +  bksge::declval<J2>()),
		typename T4 = decltype(bksge::declval<I2&>() -= bksge::declval<D >()),
		typename T5 = decltype(bksge::declval<J2 >() -  bksge::declval<D >()),
		typename T6 = decltype(bksge::declval<J2 >()[bksge::declval<D>()])
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<T1, I2&>,
		bksge::same_as<T2, I2>,
#if !(defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920))
		bksge::same_as<T3, I2>,
#endif
		bksge::same_as<T4, I2&>,
		bksge::same_as<T5, I2>,
		bksge::same_as<T6, bksge::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using random_access_iterator =
	typename detail::random_access_iterator_impl<Iter>::type;

template <typename Iter>
using is_random_access_iterator = random_access_iterator<Iter>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP
