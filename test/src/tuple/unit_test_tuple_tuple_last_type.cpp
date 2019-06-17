/**
 *	@file	unit_test_tuple_tuple_last_type.cpp
 *
 *	@brief	tuple_last_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tuple/tuple_last_type.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <type_traits>
#include "my_tuple.hpp"

namespace bksge_tuple_test
{

namespace tuple_last_type_test
{

template <template <typename...> class Tuple>
void TupleLastTypeTest()
{
	static_assert(std::is_same<long,   bksge::tuple_last_type_t<Tuple<int, float, double, long>>>::value, "");
	static_assert(std::is_same<int,    bksge::tuple_last_type_t<Tuple<int, float, double, int>>>::value, "");
	static_assert(std::is_same<double, bksge::tuple_last_type_t<Tuple<int, float, double>>>::value, "");
	static_assert(std::is_same<float,  bksge::tuple_last_type_t<Tuple<int, float, float>>>::value, "");
	static_assert(std::is_same<float,  bksge::tuple_last_type_t<Tuple<int, float>>>::value, "");
	static_assert(std::is_same<int,    bksge::tuple_last_type_t<Tuple<float, int>>>::value, "");
	static_assert(std::is_same<int,    bksge::tuple_last_type_t<Tuple<int>>>::value, "");
	static_assert(std::is_same<char,   bksge::tuple_last_type_t<Tuple<char>>>::value, "");
}

GTEST_TEST(TupleTest, TupleLastTypeTest)
{
	TupleLastTypeTest<std::tuple>();
	TupleLastTypeTest<MyTuple>();
}

}	// namespace tuple_last_type_test

}	// namespace bksge_tuple_test
