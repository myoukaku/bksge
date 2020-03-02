/**
 *	@file	unit_test_fnd_functional_cref.cpp
 *
 *	@brief	cref のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/cref.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FunctionalTest, CRefTest)
{
	{
		int i = 0;
		bksge::reference_wrapper<const int> r = bksge::cref(i);
		EXPECT_TRUE(&r.get() == &i);
	}
	{
		const int i = 0;
		bksge::reference_wrapper<const int> r1 = bksge::cref(i);
		bksge::reference_wrapper<const int> r2 = bksge::cref(r1);
		EXPECT_TRUE(&r2.get() == &i);
	}
}
