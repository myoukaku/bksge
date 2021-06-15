/**
 *	@file	unit_test_system_error_error_category.cpp
 *
 *	@brief	error_category のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/system_error/error_category.hpp>
#include <bksge/fnd/system_error/error_condition.hpp>
#include <bksge/fnd/system_error/error_code.hpp>
#include <bksge/fnd/system_error/generic_category.hpp>
#include <bksge/fnd/system_error/system_category.hpp>
#include <bksge/fnd/system_error/errc.hpp>
#include <bksge/fnd/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ErrorCategoryTest, MessageTest)
{
	const bksge::error_category& e_cat1 = bksge::generic_category();
	const bksge::error_category& e_cat2 = bksge::system_category();
	bksge::string m1 = e_cat1.message(5);
	bksge::string m2 = e_cat2.message(5);
	bksge::string m3 = e_cat2.message(6);
	EXPECT_TRUE(!m1.empty());
	EXPECT_TRUE(!m2.empty());
	EXPECT_TRUE(!m3.empty());
//	EXPECT_TRUE(m1 != m2);
	EXPECT_TRUE(m1 != m3);
	EXPECT_TRUE(m2 != m3);
}

GTEST_TEST(ErrorCategoryTest, CompareTest)
{
	const bksge::error_category& e_cat1 = bksge::generic_category();
	const bksge::error_category& e_cat2 = bksge::generic_category();
	const bksge::error_category& e_cat3 = bksge::system_category();
	EXPECT_TRUE (e_cat1 == e_cat2);
	EXPECT_FALSE(e_cat1 == e_cat3);
	EXPECT_FALSE(e_cat1 != e_cat2);
	EXPECT_TRUE (e_cat1 != e_cat3);
	EXPECT_TRUE(!(e_cat1 < e_cat2) && !(e_cat2 < e_cat1));
	EXPECT_TRUE((e_cat1 < e_cat3) || (e_cat3 < e_cat1));
}

GTEST_TEST(ErrorCategoryTest, DefaultErrorConditionTest)
{
	const bksge::error_category& e_cat = bksge::generic_category();
	bksge::error_condition e_cond = e_cat.default_error_condition(static_cast<int>(bksge::errc::not_a_directory));
	EXPECT_TRUE(e_cond.category() == e_cat);
	EXPECT_TRUE(e_cond.value() == static_cast<int>(bksge::errc::not_a_directory));
}

GTEST_TEST(ErrorCategoryTest, EquivalentTest)
{
	{
		const bksge::error_category& e_cat = bksge::generic_category();
		EXPECT_TRUE (e_cat.equivalent(bksge::error_code(5, e_cat), 5));
		EXPECT_FALSE(e_cat.equivalent(bksge::error_code(5, e_cat), 6));
	}
	{
		const bksge::error_category& e_cat = bksge::generic_category();
		bksge::error_condition e_cond = e_cat.default_error_condition(5);
		EXPECT_TRUE (e_cat.equivalent(5, e_cond));
		EXPECT_FALSE(e_cat.equivalent(6, e_cond));
	}
}
