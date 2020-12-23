/**
 *	@file	unit_test_fnd_ranges_range_difference_t.cpp
 *
 *	@brief	ranges::range_difference_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::range_difference_t<C>, I>::value, "")

BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(char      [2],                  bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(char const[2],                  bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(char      (&)[2],               bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(char const(&)[2],               bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_contiguous_range<char>,    bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_random_access_range<char>, bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_bidirectional_range<char>, bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_forward_range<char>,       bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_input_range<char>,         bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_output_range<char>,        bksge::ptrdiff_t);

BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(int      [2],                  bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(int const[2],                  bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(int      (&)[2],               bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(int const(&)[2],               bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_contiguous_range<int>,    bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_random_access_range<int>, bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_bidirectional_range<int>, bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_forward_range<int>,       bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_input_range<int>,         bksge::ptrdiff_t);
BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST(test_output_range<int>,        bksge::ptrdiff_t);

#undef BKSGE_RANGES_RANGE_DIFFERENCE_T_TEST
