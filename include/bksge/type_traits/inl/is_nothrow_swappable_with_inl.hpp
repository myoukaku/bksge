/**
 *	@file	is_nothrow_swappable_with_inl.hpp
 *
 *	@brief	is_nothrow_swappable_with の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_IS_NOTHROW_SWAPPABLE_WITH_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_IS_NOTHROW_SWAPPABLE_WITH_INL_HPP

#include <bksge/type_traits/is_nothrow_swappable_with.hpp>
#include <bksge/type_traits/is_swappable_with.hpp>
#include <bksge/utility/swap.hpp>
#include <bksge/config.hpp>
#include <type_traits>
#include <utility>

namespace bksge
{

namespace is_nothrow_swappable_detail
{

using bksge::swap;

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)

template <typename T, typename U>
struct is_nothrow_swappable_with_impl_2
{
private:
	template <typename T2, typename U2>
	static std::integral_constant<bool,
		BKSGE_NOEXCEPT_EXPR(swap(std::declval<T2>(), std::declval<U2>())) &&
		BKSGE_NOEXCEPT_EXPR(swap(std::declval<U2>(), std::declval<T2>()))
	>
	test(int);

	template <typename, typename>
	static std::false_type test(...);

public:
	using type = decltype(test<T, U>(0));
};

#else

template <typename T, typename U>
struct is_nothrow_swappable_with_impl_2
{
	using type = std::true_type;
};

#endif

template <typename T, typename U>
struct is_nothrow_swappable_with_impl
	: public std::integral_constant<bool,
		bksge::is_swappable_with<T, U>::value &&
		is_nothrow_swappable_with_impl_2<T, U>::type::value
	>
{};

}	// namespace is_nothrow_swappable_detail

template <typename T, typename U>
struct is_nothrow_swappable_with
	: public is_nothrow_swappable_detail::is_nothrow_swappable_with_impl<T, U>::type
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_IS_NOTHROW_SWAPPABLE_WITH_INL_HPP
