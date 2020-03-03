/**
 *	@file	unit_test_fnd_pair_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/tuple_size.hpp>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(PairTest, TupleSizeTest)
{
#define BKSGE_PAIR_TUPLE_SIZE_TEST(T1, T2)	\
	static_assert(bksge::tuple_size<bksge::pair<T1, T2>>::value == 2, "")

	BKSGE_PAIR_TUPLE_SIZE_TEST(int, int);
	BKSGE_PAIR_TUPLE_SIZE_TEST(int, float);
	BKSGE_PAIR_TUPLE_SIZE_TEST(float, int);
	BKSGE_PAIR_TUPLE_SIZE_TEST(double, double);
	BKSGE_PAIR_TUPLE_SIZE_TEST(int, std::string);
	BKSGE_PAIR_TUPLE_SIZE_TEST(std::string, std::vector<float>);

#undef BKSGE_PAIR_TUPLE_SIZE_TEST
}
