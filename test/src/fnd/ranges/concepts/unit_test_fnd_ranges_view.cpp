﻿/**
 *	@file	unit_test_fnd_ranges_view.cpp
 *
 *	@brief	ranges::view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/view_base.hpp>
#include <bksge/fnd/ranges/concepts/enable_view.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/span.hpp>
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
#  define BKSGE_RANGES_VIEW_TEST(B, ...)	\
	static_assert(B == bksge::ranges::view<__VA_ARGS__>, "")
#else
#  define BKSGE_RANGES_VIEW_TEST(B, ...)	\
	static_assert(B == bksge::ranges::view<__VA_ARGS__>::value, "")
#endif

namespace bksge_ranges_test
{

namespace view_test
{

template<typename T>
struct test_view
	: test_random_access_range<T>, bksge::ranges::view_base
{
	test_view() : test_random_access_range<T>(nullptr, nullptr) { }
};

struct A {};
struct B {};

using test_view_A = test_view<A>;
using test_view_B = test_view<B>;

}	// namespace view_test

}	// namespace bksge_ranges_test

BKSGE_RANGES_SPECIALIZE_ENABLE_VIEW(false, bksge_ranges_test::view_test::test_view_B);

BKSGE_RANGES_VIEW_TEST(true,  bksge_ranges_test::view_test::test_view_A);
BKSGE_RANGES_VIEW_TEST(false, bksge_ranges_test::view_test::test_view_A&);
BKSGE_RANGES_VIEW_TEST(false, bksge_ranges_test::view_test::test_view_A&&);
BKSGE_RANGES_VIEW_TEST(false, bksge_ranges_test::view_test::test_view_B);
BKSGE_RANGES_VIEW_TEST(false, bksge_ranges_test::view_test::test_view_B&);
BKSGE_RANGES_VIEW_TEST(false, bksge_ranges_test::view_test::test_view_B&&);

BKSGE_RANGES_VIEW_TEST(false, int      [2]);
BKSGE_RANGES_VIEW_TEST(false, int const[2]);
BKSGE_RANGES_VIEW_TEST(false, int      []);
BKSGE_RANGES_VIEW_TEST(false, int const[]);
BKSGE_RANGES_VIEW_TEST(false, int      (&)[2]);
BKSGE_RANGES_VIEW_TEST(false, int const(&)[2]);
BKSGE_RANGES_VIEW_TEST(false, int      (&&)[2]);
BKSGE_RANGES_VIEW_TEST(false, int const(&&)[2]);
BKSGE_RANGES_VIEW_TEST(false, int      (*)[2]);
BKSGE_RANGES_VIEW_TEST(false, int const(*)[2]);
BKSGE_RANGES_VIEW_TEST(false, int      *);
BKSGE_RANGES_VIEW_TEST(false, int const*);

BKSGE_RANGES_VIEW_TEST(false, std::array<int, 2>);
BKSGE_RANGES_VIEW_TEST(false, std::vector<int>);
BKSGE_RANGES_VIEW_TEST(false, std::deque<int>);
BKSGE_RANGES_VIEW_TEST(false, std::list<int>);
BKSGE_RANGES_VIEW_TEST(false, std::forward_list<int>);
BKSGE_RANGES_VIEW_TEST(false, std::set<int>);
BKSGE_RANGES_VIEW_TEST(false, std::multiset<int>);
BKSGE_RANGES_VIEW_TEST(false, std::unordered_set<int>);
BKSGE_RANGES_VIEW_TEST(false, std::unordered_multiset<int>);
BKSGE_RANGES_VIEW_TEST(false, std::string);
#if 0	// TODO
BKSGE_RANGES_VIEW_TEST(true,  bksge::string_view);
BKSGE_RANGES_VIEW_TEST(true,  bksge::span<int>);
BKSGE_RANGES_VIEW_TEST(true,  bksge::span<int, 0>);
BKSGE_RANGES_VIEW_TEST(false, bksge::span<int, 1>);
#endif

BKSGE_RANGES_VIEW_TEST(false, test_contiguous_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_contiguous_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_contiguous_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_random_access_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_random_access_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_random_access_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_bidirectional_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_bidirectional_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_bidirectional_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_forward_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_forward_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_forward_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_input_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_input_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_input_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_output_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_output_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_output_range<int>&&);

BKSGE_RANGES_VIEW_TEST(false, test_contiguous_sized_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_contiguous_sized_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_contiguous_sized_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_random_access_sized_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_random_access_sized_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_random_access_sized_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_bidirectional_sized_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_bidirectional_sized_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_bidirectional_sized_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_forward_sized_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_forward_sized_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_forward_sized_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_input_sized_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_input_sized_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_input_sized_range<int>&&);
BKSGE_RANGES_VIEW_TEST(false, test_output_sized_range<int>);
BKSGE_RANGES_VIEW_TEST(false, test_output_sized_range<int>&);
BKSGE_RANGES_VIEW_TEST(false, test_output_sized_range<int>&&);

#undef BKSGE_RANGES_VIEW_TEST