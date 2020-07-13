/**
 *	@file	unit_test_fnd_iterator_concepts_random_access_iterator.cpp
 *
 *	@brief	random_access_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <list>
#include <string>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_RANDOM_ACCESS_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::random_access_iterator<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::random_access_iterator_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_RANDOM_ACCESS_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::random_access_iterator_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace random_access_iterator_test
{

struct A {};

BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  int*);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  const int*);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  void**);

BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, int* const);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, const int* const);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, void** const);

BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, void*);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, const void*);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, volatile void*);

BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, void(*)());
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, void(&)());

BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, void(A::*)());
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, int A::*);

BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::deque<int>::iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::deque<A>::const_iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, std::list<int>::iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(false, std::list<A>::const_iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::string::iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::string::const_iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  bksge::string_view::iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  bksge::string_view::const_iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::vector<int>::iterator);
BKSGE_RANDOM_ACCESS_ITERATOR_TEST(true,  std::vector<A>::const_iterator);

}	// namespace random_access_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_RANDOM_ACCESS_ITERATOR_TEST
