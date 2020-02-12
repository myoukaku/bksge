/**
 *	@file	float_promote_inl.hpp
 *
 *	@brief	float_promote の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_FLOAT_PROMOTE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_FLOAT_PROMOTE_INL_HPP

#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <typename... Types>
struct float_promote_impl;

template <typename T>
struct float_promote_impl<T>
	: public bksge::conditional<
		std::is_floating_point<T>::value,
		T,
		double
	>
{};

template <typename T, typename U>
struct float_promote_impl<T, U>
	: public bksge::conditional<
		std::is_same<T, long double>::value ||
		std::is_same<U, long double>::value,
		long double,
		bksge::conditional_t<
			std::is_same<T, float>::value &&
			std::is_same<U, float>::value,
			float,
			double
		>
	>
{};

template <typename T, typename U, typename... Tail>
struct float_promote_impl<T, U, Tail...>
	: public float_promote_impl<
		typename float_promote_impl<T, U>::type,
		Tail...
	>
{};

}	// namespace detail

template <typename... Types>
struct float_promote
	: public detail::float_promote_impl<
		bksge::remove_cv_t<Types>...
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_FLOAT_PROMOTE_INL_HPP
