/**
 *	@file	unit_test_fnd_ranges_contiguous_range.cpp
 *
 *	@brief	ranges::contiguous_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <string>
#include "ranges_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::contiguous_range<__VA_ARGS__>, "")
#else
#  define BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::contiguous_range<__VA_ARGS__>::value, "")
#endif

BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  int      [2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  int const[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, int      []);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, int const[]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  int      (&)[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  int const(&)[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  int      (&&)[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  int const(&&)[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, int      (*)[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, int const(*)[2]);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, int      *);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, int const*);

#if 0
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  std::array<int, 2>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  std::vector<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::deque<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::list<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::forward_list<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::set<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::multiset<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::unordered_set<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, std::unordered_multiset<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  std::string);
#endif

BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_range<int>&&);

BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_sized_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_sized_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_sized_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_sized_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_sized_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_sized_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_sized_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_sized_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_sized_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_sized_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_sized_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_sized_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_sized_range<int>&&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_sized_range<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_sized_range<int>&);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_sized_range<int>&&);

#undef BKSGE_RANGES_CONTIGUOUS_RANGE_TEST
