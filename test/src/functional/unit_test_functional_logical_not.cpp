/**
 *	@file	unit_test_functional_logical_not.cpp
 *
 *	@brief	logical_not のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/logical_not.hpp>
#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4800)	// 'int' : ブール値を 'true' または 'false' に強制的に設定します

GTEST_TEST(FunctionalTest, LogicalNotTest)
{
	{
		using type = bksge::logical_not<bool>;
		static_assert(std::is_same<type::result_type,   bool>::value, "");
		static_assert(std::is_same<type::argument_type, bool>::value, "");
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(true));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(false));
	}
	{
		using type = bksge::logical_not<int>;
		static_assert(std::is_same<type::result_type,   bool>::value, "");
		static_assert(std::is_same<type::argument_type, int>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(0));
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(1));
	}
	{
		using type = bksge::logical_not<>;
		BKSGE_CONSTEXPR_EXPECT_FALSE(type()(true));
		BKSGE_CONSTEXPR_EXPECT_TRUE (type()(false));
	}
}

BKSGE_WARNING_POP()
