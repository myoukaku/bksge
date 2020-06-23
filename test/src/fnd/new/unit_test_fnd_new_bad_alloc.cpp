/**
 *	@file	unit_test_fnd_new_bad_alloc.cpp
 *
 *	@brief	bad_alloc のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/new/bad_alloc.hpp>
#include <bksge/fnd/exception/exception.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_polymorphic.hpp>
#include <gtest/gtest.h>

GTEST_TEST(NewTest, BadAllocTest)
{
	static_assert((bksge::is_base_of<bksge::exception, bksge::bad_alloc>::value), "");
	static_assert(bksge::is_polymorphic<bksge::bad_alloc>::value, "");

	bksge::bad_alloc b;
	bksge::bad_alloc b2 = b;
	b2 = b;
	const char* w = b2.what();
	EXPECT_TRUE(w != nullptr);
}
