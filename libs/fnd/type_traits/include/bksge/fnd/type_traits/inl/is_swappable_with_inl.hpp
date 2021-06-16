/**
 *	@file	is_swappable_with_inl.hpp
 *
 *	@brief	is_swappable_with の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_SWAPPABLE_WITH_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_SWAPPABLE_WITH_INL_HPP

#include <bksge/fnd/type_traits/is_swappable_with.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace is_swappable_detail
{

using bksge::swap;

template <typename T, typename U>
struct is_swappable_with_impl
{
private:
	template <
		typename T2,
		typename U2,
		typename = decltype(
			swap(bksge::declval<T2>(), bksge::declval<U2>()),
			swap(bksge::declval<U2>(), bksge::declval<T2>()))
	>
	static bksge::true_type test(int);

	template <typename, typename>
	static bksge::false_type test(...);

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace is_swappable_detail

template <typename T, typename U>
struct is_swappable_with
	: public is_swappable_detail::is_swappable_with_impl<T, U>::type
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_SWAPPABLE_WITH_INL_HPP
