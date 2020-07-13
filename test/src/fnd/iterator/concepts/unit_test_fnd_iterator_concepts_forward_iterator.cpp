/**
 *	@file	unit_test_fnd_iterator_concepts_forward_iterator.cpp
 *
 *	@brief	forward_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
#include <streambuf>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_FORWARD_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::forward_iterator<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::forward_iterator_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_FORWARD_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::forward_iterator_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace forward_iterator_test
{

struct A {};

BKSGE_FORWARD_ITERATOR_TEST(true,  int*);
BKSGE_FORWARD_ITERATOR_TEST(true,  const int*);
BKSGE_FORWARD_ITERATOR_TEST(true,  void**);

BKSGE_FORWARD_ITERATOR_TEST(false, int* const);
BKSGE_FORWARD_ITERATOR_TEST(false, const int* const);
BKSGE_FORWARD_ITERATOR_TEST(false, void** const);

BKSGE_FORWARD_ITERATOR_TEST(false, void*);
BKSGE_FORWARD_ITERATOR_TEST(false, const void*);
BKSGE_FORWARD_ITERATOR_TEST(false, volatile void*);

BKSGE_FORWARD_ITERATOR_TEST(false, void(*)());
BKSGE_FORWARD_ITERATOR_TEST(false, void(&)());

BKSGE_FORWARD_ITERATOR_TEST(false, void(A::*)());
BKSGE_FORWARD_ITERATOR_TEST(false, int A::*);

BKSGE_FORWARD_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::deque<int>::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::deque<A>::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::forward_list<int>::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::forward_list<A>::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::list<int>::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::list<A>::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::string::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::string::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  bksge::string_view::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  bksge::string_view::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::vector<int>::iterator);
BKSGE_FORWARD_ITERATOR_TEST(true,  std::vector<A>::const_iterator);
BKSGE_FORWARD_ITERATOR_TEST(false, std::istreambuf_iterator<char>);
BKSGE_FORWARD_ITERATOR_TEST(false, std::ostreambuf_iterator<char>);

}	// namespace forward_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_FORWARD_ITERATOR_TEST
