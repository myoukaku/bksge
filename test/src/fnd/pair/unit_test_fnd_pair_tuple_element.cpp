/**
 *	@file	unit_test_fnd_pair_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/tuple_element.hpp>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(PairTest, TupleElementTest)
{
#define BKSGE_PAIR_TUPLE_ELEMENT_TEST(PAIR, I, T)	\
	static_assert(bksge::is_same<bksge::tuple_element<I, PAIR>::type, T>::value, "");	\
	static_assert(bksge::is_same<bksge::tuple_element_t<I, PAIR>, T>::value, "")

	{
		using type = bksge::pair<int, int>;
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 0, int);
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 1, int);
	}
	{
		using type = bksge::pair<int, float>;
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 0, int);
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 1, float);
	}
	{
		using type = bksge::pair<float, int>;
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 0, float);
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 1, int);
	}
	{
		using type = bksge::pair<float, std::string>;
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 0, float);
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 1, std::string);
	}
	{
		using type = bksge::pair<std::string, std::vector<int>>;
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 0, std::string);
		BKSGE_PAIR_TUPLE_ELEMENT_TEST(type, 1, std::vector<int>);
	}

#undef BKSGE_PAIR_TUPLE_ELEMENT_TEST
}
