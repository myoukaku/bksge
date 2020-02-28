/**
 *	@file	is_convertible_inl.hpp
 *
 *	@brief	is_convertible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_CONVERTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_CONVERTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_convertible.hpp>

#if defined(_MSC_VER)

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_rvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/detail/is_same_or_base_of.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename From, typename To>
struct is_convertible_impl
	: public bksge::bool_constant<
		__is_convertible_to(From, To)
	>
{};

template <typename T>
struct is_const_reference
	: public bksge::bool_constant<
		bksge::is_lvalue_reference<T>::value &&
		bksge::is_const<bksge::remove_reference_t<T>>::value &&
		!bksge::is_volatile<bksge::remove_reference_t<T>>::value
	>
{};

template <typename From, typename To,
	typename F0 = bksge::remove_cvref_t<From>,
	typename T0 = bksge::remove_cvref_t<To>
>
struct is_convertible_impl_ref_ref
	: public bksge::conditional_t<
		detail::is_same_or_base_of<T0, F0>::value,
		is_convertible_impl<From, To>,
		bksge::is_convertible<bksge::remove_reference_t<From>, To>
	>
{};

template <typename From, typename To>
struct is_convertible_impl_ref
	: public bksge::conditional_t<
		bksge::is_lvalue_reference<From>::value,
		is_convertible_impl_ref_ref<From, To>,
		bksge::conditional_t<
			!is_const_reference<To>::value,
			bksge::false_type,
			is_convertible_impl<From, To>
		>
	>
{};

template <typename From, typename To>
struct is_convertible_impl_rvalue_ref
	: public bksge::conditional_t<
		bksge::is_lvalue_reference<From>::value,
		is_convertible_impl_ref_ref<From, To>,
		is_convertible_impl<From, To>
	>
{};

template <typename From, typename To>
struct is_convertible
	: public
		bksge::conditional_t<
			bksge::is_lvalue_reference<To>::value,
			is_convertible_impl_ref<From, To>,
			bksge::conditional_t<
				bksge::is_rvalue_reference<To>::value,
				is_convertible_impl_rvalue_ref<From, To>,
				is_convertible_impl<From, To>
			>
		>
{};

}	// namespace detail

template <typename From, typename To>
struct is_convertible
	: public detail::is_convertible<From, To>
{};

}	// namespace bksge

#else // defined(_MSC_VER)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename From, typename To>
struct is_convertible
	: public detail::constant_wrapper<
		std::is_convertible<From, To>
	>
{};

}	// namespace bksge

#endif // defined(_MSC_VER)

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_CONVERTIBLE_INL_HPP
