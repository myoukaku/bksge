/**
 *	@file	unit_test_fnd_ranges_output_range.cpp
 *
 *	@brief	ranges::output_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/concepts/output_range.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <deque>
#include <set>
#include <unordered_set>
#include "ranges_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_RANGES_OUTPUT_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::output_range<__VA_ARGS__>, "")
#else
#  define BKSGE_RANGES_OUTPUT_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::output_range<__VA_ARGS__>::value, "")
#endif

BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  int      [2],     int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int const[2],     int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int      [],      int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int const[],      int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  int      (&)[2],  int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int const(&)[2],  int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  int      (&&)[2], int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int const(&&)[2], int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int      (*)[2],  int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int const(*)[2],  int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int      *,       int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, int const*,       int);

BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  std::array<int, 2>,           int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  bksge::vector<int>,             int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  std::deque<int>,              int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  bksge::list<int>,               int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  bksge::forward_list<int>,       int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, std::set<int>,                int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, std::multiset<int>,           int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, std::unordered_set<int>,      int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, std::unordered_multiset<int>, int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  bksge::string,                char);

BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_range<int>,            int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_range<int>&,           int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_range<int>&&,          int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_range<int>,         int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_range<int>&,        int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_range<int>&&,       int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_range<int>,         int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_range<int>&,        int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_range<int>&&,       int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_range<int>,               int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_range<int>&,              int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_range<int>&&,             int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, test_input_range<int>,                 int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, test_input_range<int>&,                int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, test_input_range<int>&&,               int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_output_range<int>,                int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_output_range<int>&,               int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_output_range<int>&&,              int);

BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_sized_range<int>,      int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_sized_range<int>&,     int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_sized_range<int>&&,    int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_sized_range<int>,   int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_sized_range<int>&,  int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_sized_range<int>&&, int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_sized_range<int>,   int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_sized_range<int>&,  int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_sized_range<int>&&, int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_sized_range<int>,         int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_sized_range<int>&,        int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_sized_range<int>&&,       int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, test_input_sized_range<int>,           int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, test_input_sized_range<int>&,          int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(false, test_input_sized_range<int>&&,         int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_output_sized_range<int>,          int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_output_sized_range<int>&,         int);
BKSGE_RANGES_OUTPUT_RANGE_TEST(true,  test_output_sized_range<int>&&,        int);

#undef BKSGE_RANGES_OUTPUT_RANGE_TEST
