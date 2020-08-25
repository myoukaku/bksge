/**
 *	@file	unit_test_fnd_functional_equal_to.cpp
 *
 *	@brief	equal_to のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace equal_to_test
{

template <typename T, typename = void>
struct has_is_transparent
	: public bksge::false_type {};

template <typename T>
struct has_is_transparent<T, bksge::void_t<typename T::is_transparent>>
	: public bksge::true_type {};

GTEST_TEST(FunctionalTest, EqualToTest)
{
	{
		using type = bksge::equal_to<int>;
		static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(0, 0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(2, 3));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::equal_to<float>;
		static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		static_assert(bksge::is_same<type::first_argument_type,  float>::value, "");
		static_assert(bksge::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(0.5,  0.5));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(0.5, -0.5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::equal_to<>;
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(1, 1.0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(1.5, 2U));
		EXPECT_TRUE (type()(std::string("Hello"), "Hello"));
		EXPECT_FALSE(type()(std::string("Hello"), "hello"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace equal_to_test

}	// namespace bksge_functional_test
