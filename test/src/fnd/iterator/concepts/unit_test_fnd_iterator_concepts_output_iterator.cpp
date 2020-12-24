/**
 *	@file	unit_test_fnd_iterator_concepts_output_iterator.cpp
 *
 *	@brief	output_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/output_iterator.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <set>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::output_iterator<__VA_ARGS__>, "")
#else
#  define BKSGE_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::output_iterator<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace output_iterator_test
{

struct A {};

BKSGE_OUTPUT_ITERATOR_TEST(true,  int*, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  int*, const int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  int*, long);
BKSGE_OUTPUT_ITERATOR_TEST(true,  void**, void*);
BKSGE_OUTPUT_ITERATOR_TEST(true,  void**, long*);
BKSGE_OUTPUT_ITERATOR_TEST(false, const int*, int);

BKSGE_OUTPUT_ITERATOR_TEST(false, int* const, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, const int* const, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, void** const, void*);

BKSGE_OUTPUT_ITERATOR_TEST(false, void*, void);
BKSGE_OUTPUT_ITERATOR_TEST(false, const void*, void);
BKSGE_OUTPUT_ITERATOR_TEST(false, const void*, void*);
BKSGE_OUTPUT_ITERATOR_TEST(false, volatile void*, void);
BKSGE_OUTPUT_ITERATOR_TEST(false, volatile void*, void*);

BKSGE_OUTPUT_ITERATOR_TEST(false, void(*)(), void(&)());
BKSGE_OUTPUT_ITERATOR_TEST(false, void(&)(), void(&)());
BKSGE_OUTPUT_ITERATOR_TEST(true,  void(**)(), void(*)());
BKSGE_OUTPUT_ITERATOR_TEST(true,  void(**)(), void(&)());

// Avoid gcc 7 internal compiler error
#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 80000))
BKSGE_OUTPUT_ITERATOR_TEST(false, void(A::*)(), A*);
BKSGE_OUTPUT_ITERATOR_TEST(false, void(A::*)(), void(A::*)());
#endif
BKSGE_OUTPUT_ITERATOR_TEST(false, int A::*, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, int A::*, int A::*);

BKSGE_OUTPUT_ITERATOR_TEST(true,  std::array<int, 1>::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  std::array<A, 1>::iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::array<int, 1>::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::array<A, 1>::const_iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(true,  std::deque<int>::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  std::deque<A>::iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::deque<int>::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::deque<A>::const_iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::forward_list<int>::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::forward_list<A>::iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::forward_list<int>::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::forward_list<A>::const_iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::list<int>::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::list<A>::iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::list<int>::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::list<A>::const_iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::set<int>::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::set<A>::iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::set<int>::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, std::set<A>::const_iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::string::iterator, char);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::string::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::string::const_iterator, char);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::string::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::string_view::iterator, char);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::string_view::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::string_view::const_iterator, char);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::string_view::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::vector<int>::iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bksge::vector<A>::iterator, A);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::vector<int>::const_iterator, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, bksge::vector<A>::const_iterator, A);

BKSGE_OUTPUT_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>,     int);
BKSGE_OUTPUT_ITERATOR_TEST(false, incrementable_wrapper<int>,            int);
BKSGE_OUTPUT_ITERATOR_TEST(false, indirectly_readable_wrapper<int>,      int);
BKSGE_OUTPUT_ITERATOR_TEST(false, indirectly_writable_wrapper<int>,      int);
BKSGE_OUTPUT_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>, int);
BKSGE_OUTPUT_ITERATOR_TEST(false, input_iterator_wrapper<int>,           int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  output_iterator_wrapper<int>,          int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  forward_iterator_wrapper<int>,         int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  bidirectional_iterator_wrapper<int>,   int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>,   int);
BKSGE_OUTPUT_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>,      int);

}	// namespace output_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_OUTPUT_ITERATOR_TEST
