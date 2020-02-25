/**
 *	@file	unit_test_fnd_optional_make_optional.cpp
 *
 *	@brief	make_optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/make_optional.hpp>
#include <bksge/fnd/optional/optional.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

GTEST_TEST(OptionalTest, MakeOptionalTest)
{
	BKSGE_CONSTEXPR const int i = 42;
	auto o = bksge::make_optional(i);	// TODO constexprにする
	static_assert(std::is_same<decltype(o), bksge::optional<int>>::value, "");
	EXPECT_TRUE(o && *o == 42);
	EXPECT_TRUE(&*o != &i);
}
