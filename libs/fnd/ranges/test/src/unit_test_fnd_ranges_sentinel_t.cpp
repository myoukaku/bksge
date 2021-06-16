/**
 *	@file	unit_test_fnd_ranges_sentinel_t.cpp
 *
 *	@brief	ranges::sentinel_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_SENTINEL_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::sentinel_t<C>, I>::value, "")

BKSGE_RANGES_SENTINEL_T_TEST(char      [2],                  char      *);
BKSGE_RANGES_SENTINEL_T_TEST(char const[2],                  char const*);
BKSGE_RANGES_SENTINEL_T_TEST(char      (&)[2],               char      *);
BKSGE_RANGES_SENTINEL_T_TEST(char const(&)[2],               char const*);
BKSGE_RANGES_SENTINEL_T_TEST(test_contiguous_range<char>,    test_contiguous_range<char>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_random_access_range<char>, test_random_access_range<char>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_bidirectional_range<char>, test_bidirectional_range<char>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_forward_range<char>,       test_forward_range<char>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_input_range<char>,         test_input_range<char>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_output_range<char>,        test_output_range<char>::sentinel);

BKSGE_RANGES_SENTINEL_T_TEST(int      [2],                  int      *);
BKSGE_RANGES_SENTINEL_T_TEST(int const[2],                  int const*);
BKSGE_RANGES_SENTINEL_T_TEST(int      (&)[2],               int      *);
BKSGE_RANGES_SENTINEL_T_TEST(int const(&)[2],               int const*);
BKSGE_RANGES_SENTINEL_T_TEST(test_contiguous_range<int>,    test_contiguous_range<int>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_random_access_range<int>, test_random_access_range<int>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_bidirectional_range<int>, test_bidirectional_range<int>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_forward_range<int>,       test_forward_range<int>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_input_range<int>,         test_input_range<int>::sentinel);
BKSGE_RANGES_SENTINEL_T_TEST(test_output_range<int>,        test_output_range<int>::sentinel);

#undef BKSGE_RANGES_SENTINEL_T_TEST
