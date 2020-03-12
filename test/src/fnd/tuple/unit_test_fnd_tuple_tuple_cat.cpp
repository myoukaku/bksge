/**
 *	@file	unit_test_fnd_tuple_tuple_cat.cpp
 *
 *	@brief	tuple_cat のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_cat.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/tuple/tie.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/get.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include <array>
#include "tuple_test_utility.hpp"
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

GTEST_TEST(TupleTest, TupleCatTest)
{
	{
		bksge::tuple<> t = bksge::tuple_cat();
		((void)t); // Prevent unused warning
	}
	{
		bksge::tuple<> t1;
		bksge::tuple<> t2 = bksge::tuple_cat(t1);
		((void)t2); // Prevent unused warning
	}
	{
		bksge::tuple<> t = bksge::tuple_cat(bksge::tuple<>());
		((void)t); // Prevent unused warning
	}
#if 0	// TODO
	{
		bksge::tuple<> t = bksge::tuple_cat(std::array<int, 0>());
		((void)t); // Prevent unused warning
	}
#endif
	{
		bksge::tuple<int> t1(1);
		bksge::tuple<int> t = bksge::tuple_cat(t1);
		EXPECT_EQ(bksge::get<0>(t), 1);
	}

	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<> t = bksge::tuple_cat();
		((void)t); // Prevent unused warning
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<> t1;
		BKSGE_CXX14_CONSTEXPR bksge::tuple<> t2 = bksge::tuple_cat(t1);
		((void)t2); // Prevent unused warning
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<> t = bksge::tuple_cat(bksge::tuple<>());
		((void)t); // Prevent unused warning
	}
#if 0	// TODO
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<> t = bksge::tuple_cat(std::array<int, 0>());
		((void)t); // Prevent unused warning
	}
#endif
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t1(1);
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t = bksge::tuple_cat(t1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 1);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t1(1);
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, int> t = bksge::tuple_cat(t1, t1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		bksge::tuple<int, MoveOnly> t =
			bksge::tuple_cat(bksge::tuple<int, MoveOnly>(1, 2));
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<1>(t), 2);
	}
#if 0	// TODO
	{
		bksge::tuple<int, int, int> t = bksge::tuple_cat(std::array<int, 3>());
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 0);
		EXPECT_EQ(bksge::get<2>(t), 0);
	}
#endif
	{
		bksge::tuple<int, MoveOnly> t = bksge::tuple_cat(bksge::pair<int, MoveOnly>(2, 1));
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		bksge::tuple<> t1;
		bksge::tuple<> t2;
		bksge::tuple<> t3 = bksge::tuple_cat(t1, t2);
		((void)t3); // Prevent unused warning
	}
	{
		bksge::tuple<> t1;
		bksge::tuple<int> t2(2);
		bksge::tuple<int> t3 = bksge::tuple_cat(t1, t2);
		EXPECT_EQ(bksge::get<0>(t3), 2);
	}
	{
		bksge::tuple<> t1;
		bksge::tuple<int> t2(2);
		bksge::tuple<int> t3 = bksge::tuple_cat(t2, t1);
		EXPECT_EQ(bksge::get<0>(t3), 2);
	}
	{
		bksge::tuple<int*> t1;
		bksge::tuple<int> t2(2);
		bksge::tuple<int*, int> t3 = bksge::tuple_cat(t1, t2);
		EXPECT_EQ(bksge::get<0>(t3), nullptr);
		EXPECT_EQ(bksge::get<1>(t3), 2);
	}
	{
		bksge::tuple<int*> t1;
		bksge::tuple<int> t2(2);
		bksge::tuple<int, int*> t3 = bksge::tuple_cat(t2, t1);
		EXPECT_EQ(bksge::get<0>(t3), 2);
		EXPECT_EQ(bksge::get<1>(t3), nullptr);
	}
	{
		bksge::tuple<int*> t1;
		bksge::tuple<int, double> t2(2, 3.5);
		bksge::tuple<int*, int, double> t3 = bksge::tuple_cat(t1, t2);
		EXPECT_EQ(bksge::get<0>(t3), nullptr);
		EXPECT_EQ(bksge::get<1>(t3), 2);
		EXPECT_EQ(bksge::get<2>(t3), 3.5);
	}
	{
		bksge::tuple<int*> t1;
		bksge::tuple<int, double> t2(2, 3.5);
		bksge::tuple<int, double, int*> t3 = bksge::tuple_cat(t2, t1);
		EXPECT_EQ(bksge::get<0>(t3), 2);
		EXPECT_EQ(bksge::get<1>(t3), 3.5);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
	}
	{
		bksge::tuple<int*, MoveOnly> t1(nullptr, 1);
		bksge::tuple<int, double> t2(2, 3.5);
		bksge::tuple<int*, MoveOnly, int, double> t3 =
			bksge::tuple_cat(bksge::move(t1), t2);
		EXPECT_EQ(bksge::get<0>(t3), nullptr);
		EXPECT_EQ(bksge::get<1>(t3), 1);
		EXPECT_EQ(bksge::get<2>(t3), 2);
		EXPECT_EQ(bksge::get<3>(t3), 3.5);
	}
	{
		bksge::tuple<int*, MoveOnly> t1(nullptr, 1);
		bksge::tuple<int, double> t2(2, 3.5);
		bksge::tuple<int, double, int*, MoveOnly> t3 =
			bksge::tuple_cat(t2, bksge::move(t1));
		EXPECT_EQ(bksge::get<0>(t3), 2);
		EXPECT_EQ(bksge::get<1>(t3), 3.5);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
		EXPECT_EQ(bksge::get<3>(t3), 1);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly> t1(1, 2);
		bksge::tuple<int*, MoveOnly> t2(nullptr, 4);
		bksge::tuple<MoveOnly, MoveOnly, int*, MoveOnly> t3 =
			bksge::tuple_cat(bksge::move(t1), bksge::move(t2));
		EXPECT_EQ(bksge::get<0>(t3), 1);
		EXPECT_EQ(bksge::get<1>(t3), 2);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
		EXPECT_EQ(bksge::get<3>(t3), 4);
	}

	{
		bksge::tuple<MoveOnly, MoveOnly> t1(1, 2);
		bksge::tuple<int*, MoveOnly> t2(nullptr, 4);
		bksge::tuple<MoveOnly, MoveOnly, int*, MoveOnly> t3 =
			bksge::tuple_cat(bksge::tuple<>(),
				bksge::move(t1),
				bksge::move(t2));
		EXPECT_EQ(bksge::get<0>(t3), 1);
		EXPECT_EQ(bksge::get<1>(t3), 2);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
		EXPECT_EQ(bksge::get<3>(t3), 4);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly> t1(1, 2);
		bksge::tuple<int*, MoveOnly> t2(nullptr, 4);
		bksge::tuple<MoveOnly, MoveOnly, int*, MoveOnly> t3 =
			bksge::tuple_cat(bksge::move(t1),
				bksge::tuple<>(),
				bksge::move(t2));
		EXPECT_EQ(bksge::get<0>(t3), 1);
		EXPECT_EQ(bksge::get<1>(t3), 2);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
		EXPECT_EQ(bksge::get<3>(t3), 4);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly> t1(1, 2);
		bksge::tuple<int*, MoveOnly> t2(nullptr, 4);
		bksge::tuple<MoveOnly, MoveOnly, int*, MoveOnly> t3 =
			bksge::tuple_cat(bksge::move(t1),
				bksge::move(t2),
				bksge::tuple<>());
		EXPECT_EQ(bksge::get<0>(t3), 1);
		EXPECT_EQ(bksge::get<1>(t3), 2);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
		EXPECT_EQ(bksge::get<3>(t3), 4);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly> t1(1, 2);
		bksge::tuple<int*, MoveOnly> t2(nullptr, 4);
		bksge::tuple<MoveOnly, MoveOnly, int*, MoveOnly, int> t3 =
			bksge::tuple_cat(bksge::move(t1),
				bksge::move(t2),
				bksge::tuple<int>(5));
		EXPECT_EQ(bksge::get<0>(t3), 1);
		EXPECT_EQ(bksge::get<1>(t3), 2);
		EXPECT_EQ(bksge::get<2>(t3), nullptr);
		EXPECT_EQ(bksge::get<3>(t3), 4);
		EXPECT_EQ(bksge::get<4>(t3), 5);
	}
	{
		auto t1 = bksge::tuple_cat(
			bksge::make_tuple(bksge::make_tuple(1)),
			bksge::make_tuple()
		);
		EXPECT_TRUE(t1 == bksge::make_tuple(bksge::make_tuple(1)));

		auto t2 = bksge::tuple_cat(
			bksge::make_tuple(bksge::make_tuple(1)),
			bksge::make_tuple(bksge::make_tuple(2))
		);
		EXPECT_TRUE(t2 == bksge::make_tuple(bksge::make_tuple(1), bksge::make_tuple(2)));
	}
}

}	// namespace bksge_tuple_test
