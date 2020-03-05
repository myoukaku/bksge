/**
 *	@file	unit_test_fnd_tuple_make_tuple.cpp
 *
 *	@brief	make_tuple のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <bksge/fnd/functional/ref.hpp>
#include <bksge/fnd/functional/cref.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(TupleTest, MakeTupleTest)
{
	{
		int i = 0;
		float j = 0;
		bksge::tuple<int, int&, float&> t =
			bksge::make_tuple(1, bksge::ref(i), bksge::ref(j));
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<1>(t), 0);
		EXPECT_EQ(bksge::get<2>(t), 0);
		i = 2;
		j = 3.5;
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<1>(t), 2);
		EXPECT_EQ(bksge::get<2>(t), 3.5);
		bksge::get<1>(t) = 0;
		bksge::get<2>(t) = 0;
		EXPECT_EQ(i, 0);
		EXPECT_EQ(j, 0);
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::make_tuple(0, 1, 3.14);
		BKSGE_CXX14_CONSTEXPR int i1 = bksge::get<1>(t1);
		BKSGE_CXX14_CONSTEXPR double d1 = bksge::get<2>(t1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(i1, 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(d1, 3.14);
	}
}
