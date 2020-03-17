/**
 *	@file	test_convertible.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_VARIANT_TEST_CONVERTIBLE_HPP
#define UNIT_TEST_FND_VARIANT_TEST_CONVERTIBLE_HPP

namespace bksge_variant_test
{

namespace detail
{

template <class Tp> void eat_type(Tp);

template <class Tp, class ...Args>
constexpr auto test_convertible_imp(int)
-> decltype(eat_type<Tp>({std::declval<Args>()...}), true)
{
	return true;
}

template <class Tp, class ...Args>
constexpr auto test_convertible_imp(long) -> bool
{
	return false;
}

}	// namespace detail

template <class Tp, class ...Args>
constexpr bool test_convertible()
{
	return detail::test_convertible_imp<Tp, Args...>(0);
}

}	// namespace bksge_variant_test

#endif // UNIT_TEST_FND_VARIANT_TEST_CONVERTIBLE_HPP
