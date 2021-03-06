﻿/**
 *	@file	sized_sentinel_for.hpp
 *
 *	@brief	sized_sentinel_for の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/disable_sized_sentinel_for.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Sent, typename Iter>
concept sized_sentinel_for =
	bksge::sentinel_for<Sent, Iter> &&
	!BKSGE_DISABLE_SIZED_SENTINEL_FOR(bksge::remove_cv_t<Sent>, bksge::remove_cv_t<Iter>) &&
	requires(Iter const& i, Sent const& s)
	{
		{ s - i } -> bksge::same_as<bksge::iter_difference_t<Iter>>;
		{ i - s } -> bksge::same_as<bksge::iter_difference_t<Iter>>;
	};

template <typename Sent, typename Iter>
using is_sized_sentinel_for = bksge::bool_constant<sized_sentinel_for<Sent, Iter>>;

#else

namespace detail
{

template <typename Sent, typename Iter>
struct sized_sentinel_for_impl
{
private:
	template <typename S2, typename I2,
		typename = bksge::enable_if_t<bksge::sentinel_for<S2, I2>::value>,
		typename = bksge::enable_if_t<
			!BKSGE_DISABLE_SIZED_SENTINEL_FOR(bksge::remove_cv_t<S2>, bksge::remove_cv_t<I2>)>,
		typename D1 = decltype(bksge::declval<S2 const&>() - bksge::declval<I2 const&>()),
		typename D2 = decltype(bksge::declval<I2 const&>() - bksge::declval<S2 const&>()),
		typename D3 = bksge::iter_difference_t<I2>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<D1, D3>,
		bksge::same_as<D2, D3>
	>;

	template <typename S2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Sent, Iter>(0));
};

}	// namespace detail

template <typename Sent, typename Iter>
using sized_sentinel_for =
	typename detail::sized_sentinel_for_impl<Sent, Iter>::type;

template <typename Sent, typename Iter>
using is_sized_sentinel_for = bksge::bool_constant<sized_sentinel_for<Sent, Iter>::value>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_SIZED_SENTINEL_FOR_HPP
