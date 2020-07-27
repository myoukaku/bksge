/**
 *	@file	unit_test_fnd_ranges_iterator_t.cpp
 *
 *	@brief	ranges::iterator_t のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define BKSGE_RANGES_ITERATOR_T_TEST(C, I)	\
	static_assert(bksge::is_same<bksge::ranges::iterator_t<C>, I>::value, "")

BKSGE_RANGES_ITERATOR_T_TEST(char      [2],                  char      *);
BKSGE_RANGES_ITERATOR_T_TEST(char const[2],                  char const*);
BKSGE_RANGES_ITERATOR_T_TEST(char      (&)[2],               char      *);
BKSGE_RANGES_ITERATOR_T_TEST(char const(&)[2],               char const*);
BKSGE_RANGES_ITERATOR_T_TEST(test_contiguous_range<char>,    contiguous_iterator_wrapper<char>);
BKSGE_RANGES_ITERATOR_T_TEST(test_random_access_range<char>, random_access_iterator_wrapper<char>);
BKSGE_RANGES_ITERATOR_T_TEST(test_bidirectional_range<char>, bidirectional_iterator_wrapper<char>);
BKSGE_RANGES_ITERATOR_T_TEST(test_forward_range<char>,       forward_iterator_wrapper<char>);
BKSGE_RANGES_ITERATOR_T_TEST(test_input_range<char>,         input_iterator_wrapper<char>);
BKSGE_RANGES_ITERATOR_T_TEST(test_output_range<char>,        output_iterator_wrapper<char>);

BKSGE_RANGES_ITERATOR_T_TEST(int      [2],                  int      *);
BKSGE_RANGES_ITERATOR_T_TEST(int const[2],                  int const*);
BKSGE_RANGES_ITERATOR_T_TEST(int      (&)[2],               int      *);
BKSGE_RANGES_ITERATOR_T_TEST(int const(&)[2],               int const*);
BKSGE_RANGES_ITERATOR_T_TEST(test_contiguous_range<int>,    contiguous_iterator_wrapper<int>);
BKSGE_RANGES_ITERATOR_T_TEST(test_random_access_range<int>, random_access_iterator_wrapper<int>);
BKSGE_RANGES_ITERATOR_T_TEST(test_bidirectional_range<int>, bidirectional_iterator_wrapper<int>);
BKSGE_RANGES_ITERATOR_T_TEST(test_forward_range<int>,       forward_iterator_wrapper<int>);
BKSGE_RANGES_ITERATOR_T_TEST(test_input_range<int>,         input_iterator_wrapper<int>);
BKSGE_RANGES_ITERATOR_T_TEST(test_output_range<int>,        output_iterator_wrapper<int>);

#undef BKSGE_RANGES_ITERATOR_T_TEST
