/**
 *	@file	unit_test_fnd_tuple_tuple_head_type.cpp
 *
 *	@brief	tuple_head_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_head_type.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tuple_head_type_test
{

template <typename... Types>
struct MyTuple
{
};

template <template <typename...> class Tuple>
void TupleHeadTypeTest()
{
	static_assert(bksge::is_same<int,    bksge::tuple_head_type_t<Tuple<int, float, double, long>>>::value, "");
	static_assert(bksge::is_same<long,   bksge::tuple_head_type_t<Tuple<long, int, float, double>>>::value, "");
	static_assert(bksge::is_same<float,  bksge::tuple_head_type_t<Tuple<float, double, long>>>::value, "");
	static_assert(bksge::is_same<int,    bksge::tuple_head_type_t<Tuple<int, double, long>>>::value, "");
	static_assert(bksge::is_same<double, bksge::tuple_head_type_t<Tuple<double, long>>>::value, "");
	static_assert(bksge::is_same<long,   bksge::tuple_head_type_t<Tuple<long>>>::value, "");
	static_assert(bksge::is_same<char,   bksge::tuple_head_type_t<Tuple<char>>>::value, "");
}

GTEST_TEST(TupleTest, TupleHeadTypeTest)
{
	TupleHeadTypeTest<bksge::tuple>();
	TupleHeadTypeTest<MyTuple>();
}

}	// namespace tuple_head_type_test

}	// namespace bksge_tuple_test
