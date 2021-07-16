/**
 *	@file	is_nothrow_convertible_inl.hpp
 *
 *	@brief	is_nothrow_convertible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_CONVERTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_CONVERTIBLE_INL_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

template <typename T>
static void test_noexcept(T) noexcept;

template <typename From, typename To>
static bksge::bool_constant<noexcept(test_noexcept<To>(std::declval<From>()))>
is_nothrow_convertible_test();

template <typename From, typename To>
struct is_nothrow_convertible_helper : decltype(is_nothrow_convertible_test<From, To>())
{};

}	// namespace detail

template <typename From, typename To>
struct is_nothrow_convertible :
	bksge::disjunction<
		bksge::conjunction<
			bksge::is_void<To>,
			bksge::is_void<From>
		>,
		bksge::conjunction<
			bksge::is_convertible<From, To>,
			detail::is_nothrow_convertible_helper<From, To>
		>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_CONVERTIBLE_INL_HPP
