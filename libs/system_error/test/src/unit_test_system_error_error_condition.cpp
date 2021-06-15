/**
 *	@file	unit_test_system_error_error_condition.cpp
 *
 *	@brief	error_condition のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/system_error.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ErrorConditionTest, DefaultCtorTest)
{
	bksge::error_condition ec;
	EXPECT_TRUE(ec.value() == 0);
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorConditionTest, EnumCtorTest)
{
	bksge::error_condition ec(bksge::errc::not_a_directory);
	EXPECT_TRUE(ec.value() == static_cast<int>(bksge::errc::not_a_directory));
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorConditionTest, IntErrorCategoryCtorTest)
{
	{
		bksge::error_condition ec(6, bksge::system_category());
		EXPECT_TRUE(ec.value() == 6);
		EXPECT_TRUE(ec.category() == bksge::system_category());
	}
	{
		bksge::error_condition ec(8, bksge::generic_category());
		EXPECT_TRUE(ec.value() == 8);
		EXPECT_TRUE(ec.category() == bksge::generic_category());
	}
}

GTEST_TEST(ErrorConditionTest, AssignTest)
{
	{
		bksge::error_condition ec;
		ec.assign(6, bksge::system_category());
		EXPECT_TRUE(ec.value() == 6);
		EXPECT_TRUE(ec.category() == bksge::system_category());
	}
	{
		bksge::error_condition ec;
		ec.assign(8, bksge::generic_category());
		EXPECT_TRUE(ec.value() == 8);
		EXPECT_TRUE(ec.category() == bksge::generic_category());
	}
}

GTEST_TEST(ErrorConditionTest, ClearTest)
{
	bksge::error_condition ec;
	ec.assign(6, bksge::system_category());
	EXPECT_TRUE(ec.value() == 6);
	EXPECT_TRUE(ec.category() == bksge::system_category());
	ec.clear();
	EXPECT_TRUE(ec.value() == 0);
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorConditionTest, EnumAssignTest)
{
	bksge::error_condition ec;
	ec = bksge::errc::not_enough_memory;
	EXPECT_TRUE(ec.value() == static_cast<int>(bksge::errc::not_enough_memory));
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorConditionTest, LtTest)
{
	const bksge::error_condition ec1(6, bksge::generic_category());
	const bksge::error_condition ec2(7, bksge::generic_category());
	EXPECT_TRUE(ec1 < ec2);
}

GTEST_TEST(ErrorConditionTest, MakeErrorConditionTest)
{
	const bksge::error_condition ec1 = bksge::make_error_condition(bksge::errc::message_size);
	EXPECT_TRUE(ec1.value() == static_cast<int>(bksge::errc::message_size));
	EXPECT_TRUE(ec1.category() == bksge::generic_category());
}

GTEST_TEST(ErrorConditionTest, BoolTest)
{
	{
		const bksge::error_condition ec(6, bksge::generic_category());
		EXPECT_TRUE(static_cast<bool>(ec));
	}
	{
		const bksge::error_condition ec(0, bksge::generic_category());
		EXPECT_TRUE(!static_cast<bool>(ec));
	}
}

GTEST_TEST(ErrorConditionTest, CategoryTest)
{
	const bksge::error_condition ec(6, bksge::generic_category());
	EXPECT_TRUE(ec.category() == bksge::generic_category());
}

GTEST_TEST(ErrorConditionTest, MessageTest)
{
	const bksge::error_condition ec(6, bksge::generic_category());
	EXPECT_TRUE(ec.message() == bksge::generic_category().message(6));
}

GTEST_TEST(ErrorConditionTest, ValueTest)
{
	const bksge::error_condition ec(6, bksge::system_category());
	EXPECT_TRUE(ec.value() == 6);
}

inline void hash_test(int i)
{
	typedef bksge::error_condition T;
	typedef bksge::hash<T> H;
	H h;
	T ec(i, bksge::system_category());
	const bksge::size_t result = h(ec);
	EXPECT_TRUE(result == static_cast<bksge::size_t>(i));
	((void)result); // Prevent unused warning
}

GTEST_TEST(ErrorConditionTest, HashTest)
{
	hash_test(0);
	hash_test(2);
	hash_test(10);
}
