/**
 *	@file	unit_test_fnd_ranges_range_value_t.cpp
 *
 *	@brief	ranges::range_value_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_RANGE_VALUE_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::range_value_t<C>, I>::value, "")

BKSGE_RANGES_RANGE_VALUE_T_TEST(char      [2],                  char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(char const[2],                  char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(char      (&)[2],               char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(char const(&)[2],               char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_contiguous_range<char>,    char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_random_access_range<char>, char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_bidirectional_range<char>, char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_forward_range<char>,       char);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_input_range<char>,         char);
//BKSGE_RANGES_RANGE_VALUE_T_TEST(test_output_range<char>,        char);

BKSGE_RANGES_RANGE_VALUE_T_TEST(int      [2],                  int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(int const[2],                  int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(int      (&)[2],               int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(int const(&)[2],               int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_contiguous_range<int>,    int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_random_access_range<int>, int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_bidirectional_range<int>, int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_forward_range<int>,       int);
BKSGE_RANGES_RANGE_VALUE_T_TEST(test_input_range<int>,         int);
//BKSGE_RANGES_RANGE_VALUE_T_TEST(test_output_range<int>,        int);

#undef BKSGE_RANGES_RANGE_VALUE_T_TEST
