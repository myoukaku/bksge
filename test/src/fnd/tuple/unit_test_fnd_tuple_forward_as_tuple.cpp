/**
 *	@file	unit_test_fnd_tuple_forward_as_tuple.cpp
 *
 *	@brief	forward_as_tuple のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/forward_as_tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace forward_as_tuple_test
{

template <typename Tuple>
void
test0(const Tuple&)
{
	static_assert(bksge::tuple_size<Tuple>::value == 0, "");
}

template <typename Tuple>
void
test1a(const Tuple& t)
{
	static_assert(bksge::tuple_size<Tuple>::value == 1, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<0, Tuple>::type, int&&>::value, "");
	EXPECT_EQ(bksge::get<0>(t), 1);
}

template <typename Tuple>
void
test1b(const Tuple& t)
{
	static_assert(bksge::tuple_size<Tuple>::value == 1, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<0, Tuple>::type, int&>::value, "");
	EXPECT_EQ(bksge::get<0>(t), 2);
}

template <typename Tuple>
void
test2a(const Tuple& t)
{
	static_assert(bksge::tuple_size<Tuple>::value == 2, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<0, Tuple>::type, double&>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Tuple>::type, char&>::value, "");
	EXPECT_EQ(bksge::get<0>(t), 2.5);
	EXPECT_EQ(bksge::get<1>(t), 'a');
}

template <typename Tuple>
BKSGE_CXX14_CONSTEXPR int
test3(const Tuple&)
{
	return bksge::tuple_size<Tuple>::value;
}

GTEST_TEST(TupleTest, ForwardAsTupleTest)
{
	{
		test0(bksge::forward_as_tuple());
	}
	{
		test1a(bksge::forward_as_tuple(1));
	}
	{
		int i = 2;
		test1b(bksge::forward_as_tuple(i));
	}
	{
		double i = 2.5;
		char c = 'a';
		test2a(bksge::forward_as_tuple(i, c));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(test3(bksge::forward_as_tuple(i, c)), 2);
	}
}

}	// namespace forward_as_tuple_test

}	// namespace bksge_tuple_test
