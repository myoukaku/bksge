/**
 *	@file	unit_test_fnd_functional_greater_equal.cpp
 *
 *	@brief	greater_equal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/greater_equal.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace greater_equal_test
{

template <typename T, typename = void>
struct has_is_transparent
	: public bksge::false_type {};

template <typename T>
struct has_is_transparent<T, bksge::void_t<typename T::is_transparent>>
	: public bksge::true_type {};

GTEST_TEST(FunctionalTest, GreaterEqualTest)
{
	{
		using type = bksge::greater_equal<int>;
		//static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		//static_assert(bksge::is_same<type::first_argument_type,  int>::value, "");
		//static_assert(bksge::is_same<type::second_argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(2, 2));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(2, 3));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(2, 1));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::greater_equal<float>;
		//static_assert(bksge::is_same<type::result_type,          bool>::value, "");
		//static_assert(bksge::is_same<type::first_argument_type,  float>::value, "");
		//static_assert(bksge::is_same<type::second_argument_type, float>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(-1.5f, -1.5f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(-1.5f, -1.6f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(-1.6f, -1.5f));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = bksge::greater_equal<>;
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(3U, 3.0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(3U, 3.1));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(3U, 2.9));
		EXPECT_TRUE (type()(bksge::string("A"), "A"));
		EXPECT_FALSE(type()(bksge::string("A"), "B"));
		EXPECT_TRUE (type()(bksge::string("B"), "A"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace greater_equal_test

}	// namespace bksge_functional_test
