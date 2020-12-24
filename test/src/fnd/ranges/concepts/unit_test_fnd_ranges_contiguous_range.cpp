/**
 *	@file	unit_test_fnd_ranges_contiguous_range.cpp
 *
 *	@brief	ranges::contiguous_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/concepts/contiguous_range.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/deque.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/set.hpp>
#include <bksge/fnd/unordered_set.hpp>
#include <bksge/fnd/vector.hpp>
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
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  bksge::array<int, 2>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  bksge::vector<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::deque<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::list<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::forward_list<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::set<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::multiset<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::unordered_set<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(false, bksge::unordered_multiset<int>);
BKSGE_RANGES_CONTIGUOUS_RANGE_TEST(true,  bksge::string);
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
