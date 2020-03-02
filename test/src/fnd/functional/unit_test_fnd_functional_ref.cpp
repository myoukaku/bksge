/**
 *	@file	unit_test_fnd_functional_ref.cpp
 *
 *	@brief	ref のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/ref.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FunctionalTest, RefTest)
{
	{
		int i = 0;
		bksge::reference_wrapper<int> r = bksge::ref(i);
		EXPECT_TRUE(&r.get() == &i);
	}
	{
		int i = 0;
		bksge::reference_wrapper<int> r1 = bksge::ref(i);
		bksge::reference_wrapper<int> r2 = bksge::ref(r1);
		EXPECT_TRUE(&r2.get() == &i);
	}
}
