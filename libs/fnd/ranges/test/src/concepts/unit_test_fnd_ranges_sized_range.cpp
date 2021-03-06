﻿/**
 *	@file	unit_test_fnd_ranges_sized_range.cpp
 *
 *	@brief	ranges::sized_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/ranges/concepts/disable_sized_range.hpp>
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
#  define BKSGE_RANGES_SIZED_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::sized_range<__VA_ARGS__>, "")
#else
#  define BKSGE_RANGES_SIZED_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::sized_range<__VA_ARGS__>::value, "")
#endif

namespace bksge_ranges_test
{

namespace sized_range_test
{

struct A {};
struct B {};

}	// namespace sized_range_test

}	// namespace bksge_ranges_test

namespace bksge { namespace ranges {

template <>
BKSGE_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true,
	test_random_access_sized_range<bksge_ranges_test::sized_range_test::A>);

template <>
BKSGE_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true,
	test_bidirectional_sized_range<bksge_ranges_test::sized_range_test::B>);

}}	// bksge::ranges

BKSGE_RANGES_SIZED_RANGE_TEST(true,  int      [2]);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  int const[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(false, int      []);
BKSGE_RANGES_SIZED_RANGE_TEST(false, int const[]);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  int      (&)[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  int const(&)[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  int      (&&)[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  int const(&&)[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(false, int      (*)[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(false, int const(*)[2]);
BKSGE_RANGES_SIZED_RANGE_TEST(false, int      *);
BKSGE_RANGES_SIZED_RANGE_TEST(false, int const*);

BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::array<int, 2>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::vector<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::deque<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::list<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(false, bksge::forward_list<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::set<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::multiset<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::unordered_set<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::unordered_multiset<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  bksge::string);

BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_forward_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_forward_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_forward_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_input_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_input_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_input_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_output_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_output_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_output_range<int>&&);

BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_forward_sized_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_input_sized_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_input_sized_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_input_sized_range<int>&&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_output_sized_range<int>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_output_sized_range<int>&);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_output_sized_range<int>&&);

// Despite being disabled, this is still a sized_range because ranges::size(r)
// works, by using (ranges::end(r) - ranges::begin(r)).
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<bksge_ranges_test::sized_range_test::A>);
BKSGE_RANGES_SIZED_RANGE_TEST(true,  test_random_access_sized_range<bksge_ranges_test::sized_range_test::A>&);

// This is not a sized range because ranges::size(r) cannot use member size,
// or ADL size, and (ranges::end(r) - ranges::begin(r)) is ill-formed for
// bidirectional iterators.
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_sized_range<bksge_ranges_test::sized_range_test::B>);
BKSGE_RANGES_SIZED_RANGE_TEST(false, test_bidirectional_sized_range<bksge_ranges_test::sized_range_test::B>&);

#undef BKSGE_RANGES_SIZED_RANGE_TEST
