/**
 *	@file	is_constructible_inl.hpp
 *
 *	@brief	is_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_CONSTRUCTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_STDLIB_DINKUMWARE)

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/detail/is_constructible_helper.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if (defined(_MSC_VER) && (_MSC_VER >= 1500)) || \
	BKSGE_HAS_FEATURE(is_constructible)

template <typename T, typename... Args>
struct is_constructible
	: public bksge::bool_constant<
		__is_constructible(T, Args...)
	>
{};

#else

template <typename T, typename... Args>
struct is_constructible_impl
{
	template <typename T1, typename... Args1>
	static auto test(int) -> decltype(::new T1(bksge::declval<Args1>()...), bksge::true_type());
	template <typename T1, typename... Args1>
	static auto test(...) -> bksge::false_type;

	using type = decltype(test<T, Args...>(0));
};

template <typename T, typename... Args>
struct is_constructible
	: public is_constructible_impl<T, Args...>::type
{};

#endif

}	// namespace detail

template <typename T, typename... Args>
struct is_constructible
	: public detail::is_constructible_helper<
		detail::is_constructible, T, Args...
	>
{};

}	// namespace bksge

#elif defined(BKSGE_STDLIB_LIBSTDCPP3)

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/type_traits/detail/is_array_unknown_bounds.hpp>
#include <type_traits>

namespace bksge
{

template <typename T, typename... Args>
struct is_constructible
	: public bksge::bool_constant<
		!detail::is_array_unknown_bounds<T>::value &&
		!bksge::is_function<T>::value &&
		std::is_constructible<T, Args...>::value
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename T, typename... Args>
struct is_constructible
	: public detail::constant_wrapper<
		std::is_constructible<T, Args...>
	>
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_CONSTRUCTIBLE_INL_HPP
