/**
 *	@file	unit_test_fnd_ranges_range_size_t.cpp
 *
 *	@brief	ranges::range_size_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/range_size_t.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_RANGE_SIZE_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::range_size_t<C>, I>::value, "")

BKSGE_RANGES_RANGE_SIZE_T_TEST(int      [2],                  bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(int const[2],                  bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(int      (&)[2],               bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(int const(&)[2],               bksge::size_t);

BKSGE_RANGES_RANGE_SIZE_T_TEST(test_contiguous_range<int>,    bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(test_random_access_range<int>, bksge::size_t);
//BKSGE_RANGES_RANGE_SIZE_T_TEST(test_bidirectional_range<int>, bksge::size_t);
//BKSGE_RANGES_RANGE_SIZE_T_TEST(test_forward_range<int>,       bksge::size_t);
//BKSGE_RANGES_RANGE_SIZE_T_TEST(test_input_range<int>,         bksge::size_t);
//BKSGE_RANGES_RANGE_SIZE_T_TEST(test_output_range<int>,        bksge::size_t);

BKSGE_RANGES_RANGE_SIZE_T_TEST(test_contiguous_sized_range<int>,    bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(test_random_access_sized_range<int>, bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(test_bidirectional_sized_range<int>, bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(test_forward_sized_range<int>,       bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(test_input_sized_range<int>,         bksge::size_t);
BKSGE_RANGES_RANGE_SIZE_T_TEST(test_output_sized_range<int>,        bksge::size_t);

#undef BKSGE_RANGES_RANGE_SIZE_T_TEST
