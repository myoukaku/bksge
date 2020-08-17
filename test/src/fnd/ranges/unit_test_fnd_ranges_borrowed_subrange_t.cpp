/**
 *	@file	unit_test_fnd_ranges_borrowed_subrange_t.cpp
 *
 *	@brief	ranges::borrowed_subrange_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
#include <bksge/fnd/ranges/subrange.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/span.hpp>
#include <bksge/fnd/preprocessor/punctuation/comma.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::borrowed_subrange_t<C>, I>::value, "")

BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(char      [2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(char const[2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(char      (&)[2],                bksge::ranges::subrange<char      *>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(char const(&)[2],                bksge::ranges::subrange<char const*>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<char>,     bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<char>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<char>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<char>,        bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<char>,          bksge::ranges::dangling);
//BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<char>,         bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<char>&,    bksge::ranges::subrange<contiguous_iterator_wrapper<char>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<char>&, bksge::ranges::subrange<random_access_iterator_wrapper<char>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<char>&, bksge::ranges::subrange<bidirectional_iterator_wrapper<char>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<char>&,       bksge::ranges::subrange<forward_iterator_wrapper<char>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<char>&,         bksge::ranges::subrange<input_iterator_wrapper<char>>);
//BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<char>&,        bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(bksge::span<char>,               bksge::ranges::subrange<char*>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(bksge::span<char BKSGE_PP_COMMA() 10>, bksge::ranges::subrange<char*>);

BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(int      [2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(int const[2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(int      (&)[2],                bksge::ranges::subrange<int      *>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(int const(&)[2],                bksge::ranges::subrange<int const*>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<int>,     bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<int>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<int>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<int>,        bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<int>,          bksge::ranges::dangling);
//BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<int>,         bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<int>&,    bksge::ranges::subrange<contiguous_iterator_wrapper<int>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<int>&, bksge::ranges::subrange<random_access_iterator_wrapper<int>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<int>&, bksge::ranges::subrange<bidirectional_iterator_wrapper<int>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<int>&,       bksge::ranges::subrange<forward_iterator_wrapper<int>>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<int>&,         bksge::ranges::subrange<input_iterator_wrapper<int>>);
//BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<int>&,        bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(bksge::span<int>,               bksge::ranges::subrange<int*>);
BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST(bksge::span<int BKSGE_PP_COMMA() 10>, bksge::ranges::subrange<int*>);

#undef BKSGE_RANGES_BORROWED_SUBRANGE_T_TEST
