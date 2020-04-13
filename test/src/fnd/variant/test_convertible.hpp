/**
 *	@file	test_convertible.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_VARIANT_TEST_CONVERTIBLE_HPP
#define UNIT_TEST_FND_VARIANT_TEST_CONVERTIBLE_HPP

#include <bksge/fnd/utility/declval.hpp>

namespace bksge_variant_test
{

namespace detail
{

template <typename T> void eat_type(T);

template <typename T, typename... Args>
constexpr auto test_convertible_imp(int)
-> decltype(eat_type<T>({bksge::declval<Args>()...}), true)
{
	return true;
}

template <typename T, typename... Args>
constexpr auto test_convertible_imp(long) -> bool
{
	return false;
}

}	// namespace detail

template <typename T, typename... Args>
constexpr bool test_convertible()
{
	return detail::test_convertible_imp<T, Args...>(0);
}

}	// namespace bksge_variant_test

#endif // UNIT_TEST_FND_VARIANT_TEST_CONVERTIBLE_HPP
