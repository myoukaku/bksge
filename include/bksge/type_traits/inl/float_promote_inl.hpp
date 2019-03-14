/**
 *	@file	float_promote_inl.hpp
 *
 *	@brief	float_promote の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_FLOAT_PROMOTE_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_FLOAT_PROMOTE_INL_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <typename... Types>
struct float_promote_impl;

template <typename T>
struct float_promote_impl<T>
	: public std::conditional<
		std::is_floating_point<T>::value,
		T,
		double
	>
{};

template <typename T, typename U>
struct float_promote_impl<T, U>
	: public std::conditional<
		std::is_same<T, long double>::value ||
		std::is_same<U, long double>::value,
		long double,
		typename std::conditional<
			std::is_same<T, float>::value &&
			std::is_same<U, float>::value,
			float,
			double
		>::type
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
		typename std::remove_cv<Types>::type...
	>
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_FLOAT_PROMOTE_INL_HPP
