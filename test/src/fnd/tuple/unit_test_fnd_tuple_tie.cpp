/**
 *	@file	unit_test_fnd_tuple_tie.cpp
 *
 *	@brief	tie のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tie.hpp>
#include <bksge/fnd/tuple/ignore.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
//#include <bksge/fnd/string.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_trivial.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tie_test
{

void test_tie_constexpr()
{
	int i = 42;
	double f = 1.1;
	using ExpectT = bksge::tuple<int&, decltype(bksge::ignore)&, double&>;
	auto res = bksge::tie(i, bksge::ignore, f);
	static_assert(bksge::is_same<ExpectT, decltype(res)>::value, "");
	EXPECT_TRUE(&bksge::get<0>(res) == &i);
	EXPECT_TRUE(&bksge::get<1>(res) == &bksge::ignore);
	EXPECT_TRUE(&bksge::get<2>(res) == &f);
	// FIXME: If/when tuple gets constexpr assignment
	//res = bksge::make_tuple(101, nullptr, -1.0);
}

GTEST_TEST(TupleTest, TieTest)
{
	// TODO
	//{
	//    int i = 0;
	//    bksge::string s;
	//    bksge::tie(i, bksge::ignore, s) = bksge::make_tuple(42, 3.14, "C++");
	//    EXPECT_TRUE(i == 42);
	//    EXPECT_TRUE(s == "C++");
	//}
	{
		static constexpr int i = 42;
		static constexpr double f = 1.1;
		BKSGE_CXX14_CONSTEXPR bksge::tuple<const int &, const double &> t = bksge::tie(i, f);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(t), 1.1);
	}
	{
		test_tie_constexpr();
	}
}

}	// namespace tie_test

namespace ignore_test
{

void test_ignore_constexpr()
{
	{ // Test that bksge::ignore provides constexpr converting assignment.
		auto& res = (bksge::ignore = 42);
		EXPECT_TRUE(&res == &bksge::ignore);
	}
	{ // Test that bksge::ignore provides constexpr copy/move constructors
		auto copy = bksge::ignore;
		auto moved = bksge::move(copy);
		((void)moved);
	}
	{ // Test that bksge::ignore provides constexpr copy/move assignment
		auto copy = bksge::ignore;
		copy = bksge::ignore;
		auto moved = bksge::ignore;
		moved = bksge::move(copy);
	}
}

GTEST_TEST(TupleTest, IgnoreTest)
{
	{
		constexpr auto& ignore_v = bksge::ignore;
		((void)ignore_v);
	}
	{
		test_ignore_constexpr();
	}
	{
		static_assert(bksge::is_trivial<decltype(bksge::ignore)>::value, "");
	}
}

}	// namespace ignore_test

}	// namespace bksge_tuple_test
