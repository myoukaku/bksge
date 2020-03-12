/**
 *	@file	unit_test_fnd_tuple_tuple_count.cpp
 *
 *	@brief	tuple_count のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_count.hpp>
#include <tuple>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tuple_count_test
{

template <typename... Types>
struct MyTuple
{
};

template <template <typename...> class Tuple>
void TupleCountTest()
{
	{
		using t = Tuple<int, float, double>;

		static_assert(bksge::tuple_count<int,          t>::value == 1, "");
		static_assert(bksge::tuple_count<float,        t>::value == 1, "");
		static_assert(bksge::tuple_count<double,       t>::value == 1, "");
		static_assert(bksge::tuple_count<char,         t>::value == 0, "");
		static_assert(bksge::tuple_count<unsigned int, t>::value == 0, "");
	}
	{
		using t = Tuple<int, float, int, double, char, float, int>;

		static_assert(bksge::tuple_count<int,          t>::value == 3, "");
		static_assert(bksge::tuple_count<float,        t>::value == 2, "");
		static_assert(bksge::tuple_count<double,       t>::value == 1, "");
		static_assert(bksge::tuple_count<char,         t>::value == 1, "");
		static_assert(bksge::tuple_count<unsigned int, t>::value == 0, "");
	}
	{
		using t = Tuple<>;

		static_assert(bksge::tuple_count<int,          t>::value == 0, "");
		static_assert(bksge::tuple_count<float,        t>::value == 0, "");
		static_assert(bksge::tuple_count<double,       t>::value == 0, "");
		static_assert(bksge::tuple_count<char,         t>::value == 0, "");
		static_assert(bksge::tuple_count<unsigned int, t>::value == 0, "");
	}
}

GTEST_TEST(TupleTest, TupleCountTest)
{
	TupleCountTest<std::tuple>();
	TupleCountTest<MyTuple>();
}

}	// namespace tuple_count_test

}	// namespace bksge_tuple_test
