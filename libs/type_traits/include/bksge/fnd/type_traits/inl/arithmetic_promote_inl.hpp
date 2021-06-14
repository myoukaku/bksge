/**
 *	@file	arithmetic_promote_inl.hpp
 *
 *	@brief	arithmetic_promote の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_ARITHMETIC_PROMOTE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_ARITHMETIC_PROMOTE_INL_HPP

#include <bksge/fnd/type_traits/arithmetic_promote.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace detail
{

template <typename... T>
struct arithmetic_promote_impl;

template <typename T>
struct arithmetic_promote_impl<T>
	: public bksge::type_identity<T>
{
	static_assert(bksge::is_arithmetic<T>::value, "");
};

template <typename T, typename U>
struct arithmetic_promote_impl<T, U>
	: public bksge::decay<decltype(bksge::declval<T>() + bksge::declval<U>())>
{
	static_assert(bksge::is_arithmetic<T>::value, "");
};

template <typename T, typename U, typename... Tail>
struct arithmetic_promote_impl<T, U, Tail...>
	: public arithmetic_promote_impl<typename arithmetic_promote_impl<T, U>::type, Tail...>
{};

}	// namespace detail

template <typename... T>
struct arithmetic_promote
	: public detail::arithmetic_promote_impl<
		bksge::remove_cv_t<T>...
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_ARITHMETIC_PROMOTE_INL_HPP
