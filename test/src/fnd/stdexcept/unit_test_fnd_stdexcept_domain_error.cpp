/**
 *	@file	unit_test_fnd_stdexcept_domain_error.cpp
 *
 *	@brief	domain_error のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/stdexcept/domain_error.hpp>
#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, DomainErrorTest)
{
	static_assert(bksge::is_base_of<bksge::logic_error, bksge::domain_error>::value, "");
	static_assert(bksge::is_polymorphic<bksge::domain_error>::value, "");

	{
		char const* msg = "domain_error message 1";
		bksge::domain_error e(msg);
		EXPECT_STREQ(msg, e.what());
		bksge::domain_error e2(e);
		EXPECT_STREQ(msg, e2.what());
		e2 = e;
		EXPECT_STREQ(msg, e2.what());
	}
	{
		bksge::string msg = "domain_error message 2";
		bksge::domain_error e(msg);
		EXPECT_EQ(msg, e.what());
		bksge::domain_error e2(e);
		EXPECT_EQ(msg, e2.what());
		e2 = e;
		EXPECT_EQ(msg, e2.what());
	}
}
