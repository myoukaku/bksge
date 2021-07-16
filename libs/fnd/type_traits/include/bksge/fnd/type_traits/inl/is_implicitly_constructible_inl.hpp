/**
 *	@file	is_implicitly_constructible_inl.hpp
 *
 *	@brief	is_implicitly_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_CONSTRUCTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_constructible.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

template <bool, typename T, typename... Args>
struct is_implicitly_constructible_impl
{
private:
	template <typename T1>
	static void test_helper(T1);

	template <typename T1, typename... Args1>
	static auto test(int)
		-> decltype(test_helper<T1>({std::declval<Args1>()...}), bksge::true_type());

	template <typename T1, typename... Args1>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, Args...>(0));
};

template <typename T, typename... Args>
struct is_implicitly_constructible_impl<true, T, Args...>
	: public bksge::true_type
{};

template <bool, typename T, typename... Args>
struct is_implicitly_constructible
	: public is_implicitly_constructible_impl<
		bksge::is_trivially_constructible<T, Args...>::value,
		T, Args...
	>::type
{};

template <typename T, typename... Args>
struct is_implicitly_constructible<false, T, Args...>
	: public bksge::false_type
{};

}	// namespace detail

template <typename T, typename... Args>
struct is_implicitly_constructible
	: public detail::is_implicitly_constructible<
		bksge::is_constructible<T, Args...>::value,
		T, Args...
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_CONSTRUCTIBLE_INL_HPP
