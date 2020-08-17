/**
 *	@file	unit_test_fnd_ranges_borrowed_iterator_t.cpp
 *
 *	@brief	ranges::borrowed_iterator_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/subrange.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/span.hpp>
#include <bksge/fnd/preprocessor/punctuation/comma.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::borrowed_iterator_t<C>, I>::value, "")

BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(char      [2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(char const[2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(char      (&)[2],                char      *);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(char const(&)[2],                char const*);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<char>,     bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<char>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<char>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<char>,        bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<char>,          bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<char>,         bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<char>&,    contiguous_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<char>&, random_access_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<char>&, bidirectional_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<char>&,       forward_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<char>&,         input_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<char>&,        output_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<char*>,  char*);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<contiguous_iterator_wrapper<char>>,    contiguous_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<random_access_iterator_wrapper<char>>, random_access_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<bidirectional_iterator_wrapper<char>>, bidirectional_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<forward_iterator_wrapper<char>>,       forward_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<input_iterator_wrapper<char>>,         input_iterator_wrapper<char>);
//BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<output_iterator_wrapper<char>>,        output_iterator_wrapper<char>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::span<char>,               char*);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::span<char BKSGE_PP_COMMA() 10>, char*);

BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(int      [2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(int const[2],                   bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(int      (&)[2],                int      *);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(int const(&)[2],                int const*);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<int>,     bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<int>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<int>,  bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<int>,        bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<int>,          bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<int>,         bksge::ranges::dangling);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<int>&,    contiguous_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<int>&, random_access_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<int>&, bidirectional_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<int>&,       forward_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<int>&,         input_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<int>&,        output_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<int*>,  int*);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<contiguous_iterator_wrapper<int>>,    contiguous_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<random_access_iterator_wrapper<int>>, random_access_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<bidirectional_iterator_wrapper<int>>, bidirectional_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<forward_iterator_wrapper<int>>,       forward_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<input_iterator_wrapper<int>>,         input_iterator_wrapper<int>);
//BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::ranges::subrange<output_iterator_wrapper<int>>,        output_iterator_wrapper<int>);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::span<int>,               int*);
BKSGE_RANGES_BORROWED_ITERATOR_T_TEST(bksge::span<int BKSGE_PP_COMMA() 10>, int*);

#undef BKSGE_RANGES_BORROWED_ITERATOR_T_TEST
