/**
 *	@file	unit_test_fnd_iterator_concepts_contiguous_iterator.cpp
 *
 *	@brief	contiguous_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <list>
#include <string>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_CONTIGUOUS_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::contiguous_iterator<__VA_ARGS__>, "contiguous_iterator");	\
	static_assert(B == bksge::contiguous_iterator_t<__VA_ARGS__>::value, "contiguous_iterator_t")
#else
#  define BKSGE_CONTIGUOUS_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::contiguous_iterator_t<__VA_ARGS__>::value, "contiguous_iterator_t")
#endif

namespace bksge_iterator_test
{

namespace contiguous_iterator_test
{

struct A {};

BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  int               *);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  int const         *);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  int       volatile*);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  int const volatile*);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, int               * const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, int const         * const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, int       volatile* const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, int const volatile* const);

BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void               *);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void const         *);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void       volatile*);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void const volatile*);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void               * const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void const         * const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void       volatile* const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void const volatile* const);

BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  void               **);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  void const         **);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  void       volatile**);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  void const volatile**);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void               ** const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void const         ** const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void       volatile** const);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void const volatile** const);

BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void(*)());
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void(&)());
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  void(**)());

BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void(A::*)());
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, int A::*);

#if 0

BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::deque<int>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::deque<A>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::list<int>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::list<A>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::string::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::string::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::vector<int>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::vector<A>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::vector<bool>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::vector<bool>::const_iterator);

#endif

}	// namespace contiguous_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_CONTIGUOUS_ITERATOR_TEST
