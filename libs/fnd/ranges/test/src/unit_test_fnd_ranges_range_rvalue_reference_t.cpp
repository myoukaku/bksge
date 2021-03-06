﻿/**
 *	@file	unit_test_fnd_ranges_range_rvalue_reference_t.cpp
 *
 *	@brief	ranges::range_rvalue_reference_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/range_rvalue_reference_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::range_rvalue_reference_t<C>, I>::value, "")

BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char      [2],                  char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char const[2],                  char const&&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char      (&)[2],               char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char const(&)[2],               char const&&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_contiguous_range<char>,    char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_random_access_range<char>, char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_bidirectional_range<char>, char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_forward_range<char>,       char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_input_range<char>,         char      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_output_range<char>,        char      &&);

BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int      [2],                  int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int const[2],                  int const&&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int      (&)[2],               int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int const(&)[2],               int const&&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_contiguous_range<int>,    int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_random_access_range<int>, int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_bidirectional_range<int>, int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_forward_range<int>,       int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_input_range<int>,         int      &&);
BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_output_range<int>,        int      &&);

#undef BKSGE_RANGES_RANGE_RVALUE_REFERENCE_T_TEST
