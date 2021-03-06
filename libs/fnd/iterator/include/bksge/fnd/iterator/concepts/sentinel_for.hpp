﻿/**
 *	@file	sentinel_for.hpp
 *
 *	@brief	sentinel_for の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_SENTINEL_FOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_SENTINEL_FOR_HPP

#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/concepts/detail/weakly_eq_cmp_with.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Sent, typename Iter>
concept sentinel_for =
	bksge::semiregular<Sent> &&
	bksge::input_or_output_iterator<Iter> &&
	bksge::detail::weakly_eq_cmp_with<Sent, Iter>;

template <typename Sent, typename Iter>
using is_sentinel_for = bksge::bool_constant<sentinel_for<Sent, Iter>>;

#else

namespace detail
{

template <typename Sent, typename Iter>
struct sentinel_for_impl
{
private:
	template <typename S2, typename I2,
		typename = bksge::enable_if_t<bksge::semiregular<S2>::value>,
		typename = bksge::enable_if_t<bksge::input_or_output_iterator<I2>::value>,
		typename = bksge::enable_if_t<bksge::detail::weakly_eq_cmp_with<S2, I2>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename S2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Sent, Iter>(0));
};

}	// namespace detail

template <typename Sent, typename Iter>
using sentinel_for =
	typename detail::sentinel_for_impl<Sent, Iter>::type;

template <typename Sent, typename Iter>
using is_sentinel_for = sentinel_for<Sent, Iter>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_SENTINEL_FOR_HPP
