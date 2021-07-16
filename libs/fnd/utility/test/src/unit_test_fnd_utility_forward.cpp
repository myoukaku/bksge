/**
 *	@file	unit_test_fnd_utility_forward.cpp
 *
 *	@brief	forward のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/forward.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace forward_test
{

int func(int&)
{
	return 0;
}

int func(int&&)
{
	return 1;
}

template <typename T>
int func2(T&& x)
{
	return func(bksge::forward<T>(x));
}

GTEST_TEST(UtilityTest, ForwardTest)
{
	using std::move;

	int i = 42;
	EXPECT_EQ(1, func(42));
	EXPECT_EQ(0, func(i));
	EXPECT_EQ(1, func(move(i)));

	EXPECT_EQ(1, func2(42));
	EXPECT_EQ(0, func2(i));
	EXPECT_EQ(1, func2(move(i)));

	BKSGE_CONSTEXPR_OR_CONST int x = 123;
	BKSGE_CONSTEXPR_OR_CONST int y = bksge::forward<const int>(x);

	BKSGE_CONSTEXPR_EXPECT_EQ(123, y);
}

}	// namespace forward_test

}	// namespace bksge_utility_test
