/**
 *	@file	pair_like_convertible_from.hpp
 *
 *	@brief	pair_like_convertible_from の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP
#define BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/detail/pair_like.hpp>
#include <bksge/fnd/ranges/detail/convertible_to_non_slicing.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename V>
concept pair_like_convertible_from =
	!ranges::range<T> &&
	ranges::detail::pair_like<T> &&
	bksge::constructible_from<T, U, V> &&
	ranges::detail::convertible_to_non_slicing<U, bksge::tuple_element_t<0, T>> &&
	bksge::convertible_to<V, bksge::tuple_element_t<1, T>>;

#else

template <typename T, typename U, typename V>
struct pair_like_convertible_from_impl
{
private:
	template <typename T2, typename U2, typename V2,
		typename = bksge::enable_if_t<!ranges::range<T2>::value>,
		typename = bksge::enable_if_t<ranges::detail::pair_like<T2>::value>,
		typename = bksge::enable_if_t<bksge::constructible_from<T2, U2, V2>::value>,
		typename E0 = bksge::tuple_element_t<0, T2>,
		typename = bksge::enable_if_t<ranges::detail::convertible_to_non_slicing<U2, E0>::value>,
		typename E1 = bksge::tuple_element_t<1, T2>,
		typename = bksge::enable_if_t<bksge::convertible_to<V2, E1>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename T2, typename U2, typename V2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U, V>(0));
};

template <typename T, typename U, typename V>
using pair_like_convertible_from = typename pair_like_convertible_from_impl<T, U, V>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP
