/**
 *	@file	common_reference_inl.hpp
 *
 *	@brief	common_reference の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_COMMON_REFERENCE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_COMMON_REFERENCE_INL_HPP

#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/basic_common_reference.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/copy_cv.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/detail/common_type_fold.hpp>
#include <bksge/fnd/type_traits/detail/common_type_pack.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace detail
{

template <typename X, typename Y>
using cond_res = decltype(false ? bksge::declval<X(&)()>()() : bksge::declval<Y(&)()>()());

template <
	typename A, typename B,
	bool = bksge::is_lvalue_reference<A>::value,
	bool = bksge::is_lvalue_reference<B>::value,
	typename = bksge::void_t<>
>
struct common_ref_impl
{};

// [meta.trans.other], COMMON-REF(A, B)
template <typename A, typename B>
using common_ref = typename detail::common_ref_impl<A, B>::type;

// If A and B are both lvalue reference types, ...
template <typename X, typename Y>
struct common_ref_impl<X, Y, true, true,
	bksge::void_t<detail::cond_res<bksge::copy_cv_t<bksge::remove_reference_t<X>, bksge::remove_reference_t<Y>>&, bksge::copy_cv_t<bksge::remove_reference_t<Y>, bksge::remove_reference_t<X>>&>>>
{
	using type = detail::cond_res<bksge::copy_cv_t<bksge::remove_reference_t<X>, bksge::remove_reference_t<Y>>&, bksge::copy_cv_t<bksge::remove_reference_t<Y>, bksge::remove_reference_t<X>>&>;
};

// let C be remove_reference_t<COMMON-REF(X&, Y&)>&&
template <typename X, typename Y>
using common_ref_C = bksge::remove_reference_t<detail::common_ref<X&, Y&>>&&;

// If A and B are both rvalue reference types, ...
template <typename X, typename Y>
struct common_ref_impl<X, Y, false, false,
	bksge::enable_if_t<
		bksge::is_convertible<X, detail::common_ref_C<X, Y>>::value &&
		bksge::is_convertible<Y, detail::common_ref_C<X, Y>>::value
	>
>
{
	using type = detail::common_ref_C<X, Y>;
};

// let D be COMMON-REF(const X&, Y&)
template <typename X, typename Y>
using common_ref_D = detail::common_ref<const bksge::remove_reference_t<X>&, Y&>;

// If A is an rvalue reference and B is an lvalue reference, ...
template <typename X, typename Y>
struct common_ref_impl<X, Y, false, true,
	bksge::enable_if_t<
		bksge::is_convertible<X, detail::common_ref_D<X, Y>>::value
	>
>
{
	using type = detail::common_ref_D<X, Y>;
};

// If A is an lvalue reference and B is an rvalue reference, ...
template <typename X, typename Y>
struct common_ref_impl<X, Y, true, false>
	: public common_ref_impl<Y, X>
{};

template <typename T>
struct xref
{
	template <typename U> using type = bksge::copy_cv_t<U, T>;
};

template <typename T>
struct xref<T&>
{
	template <typename U> using type = bksge::copy_cv_t<U, T>&;
};

template <typename T>
struct xref<T&&>
{
	template <typename U> using type = bksge::copy_cv_t<U, T>&&;
};

template <typename T1, typename T2>
using basic_common_ref =
	typename bksge::basic_common_reference<
		bksge::remove_cvref_t<T1>,
		bksge::remove_cvref_t<T2>,
		detail::xref<T1>::template type,
		detail::xref<T2>::template type
	>::type;

template <typename T1, typename T2, int Bullet = 1, bool = bksge::is_reference<T1>::value && bksge::is_reference<T2>::value, typename = bksge::void_t<>>
struct common_reference_impl
	: public common_reference_impl<T1, T2, Bullet + 1>
{};

// If T1 and T2 are reference types and COMMON-REF(T1, T2) is well-formed, ...
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 1, true,
	bksge::void_t<detail::common_ref<T1, T2>>>
{
	using type = detail::common_ref<T1, T2>;
};

// Otherwise, if basic_common_reference<...>::type is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 2, B,
	bksge::void_t<detail::basic_common_ref<T1, T2>>>
{
	using type = detail::basic_common_ref<T1, T2>;
};

// Otherwise, if COND-RES(T1, T2) is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 3, B,
	bksge::void_t<detail::cond_res<T1, T2>>>
{
	using type = detail::cond_res<T1, T2>;
};

// Otherwise, if bksge::common_type_t<T1, T2> is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 4, B,
	bksge::void_t<bksge::common_type_t<T1, T2>>>
{
	using type = bksge::common_type_t<T1, T2>;
};

// Otherwise, there shall be no member type.
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 5, B, bksge::void_t<>>
{};

template <typename T1, typename T2, typename... Rest>
struct common_type_fold<
	common_reference<T1, T2>,
	detail::common_type_pack<Rest...>,
	bksge::void_t<bksge::common_reference_t<T1, T2>>
>
	: public bksge::common_reference<bksge::common_reference_t<T1, T2>, Rest...>
{};

}	// namespace detail

// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_reference<>
{};

// If sizeof...(T) is one ...
template <typename T0>
struct common_reference<T0>
{
	using type = T0;
};

// If sizeof...(T) is two ...
template <typename T1, typename T2>
struct common_reference<T1, T2>
	: public detail::common_reference_impl<T1, T2>
{};

// Otherwise, if sizeof...(T) is greater than two, ...
template <typename T1, typename T2, typename... Rest>
struct common_reference<T1, T2, Rest...>
	: public detail::common_type_fold<
		common_reference<T1, T2>,
		detail::common_type_pack<Rest...>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_COMMON_REFERENCE_INL_HPP
