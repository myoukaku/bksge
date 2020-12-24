/**
 *	@file	unit_test_fnd_iterator_concepts_contiguous_iterator.cpp
 *
 *	@brief	contiguous_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_CONTIGUOUS_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::contiguous_iterator<__VA_ARGS__>, "")
#else
#  define BKSGE_CONTIGUOUS_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::contiguous_iterator<__VA_ARGS__>::value, "")
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

// Avoid gcc 7 internal compiler error
#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 80000))
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, void(A::*)());
#endif
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, int A::*);

#if 0

BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::deque<int>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, std::deque<A>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, bksge::list<int>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, bksge::list<A>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  bksge::string::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  bksge::string::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  bksge::vector<int>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  bksge::vector<A>::const_iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, bksge::vector<bool>::iterator);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, bksge::vector<bool>::const_iterator);

#endif

BKSGE_CONTIGUOUS_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, incrementable_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, input_iterator_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, output_iterator_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, forward_iterator_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, bidirectional_iterator_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(false, random_access_iterator_wrapper<int>);
BKSGE_CONTIGUOUS_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace contiguous_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_CONTIGUOUS_ITERATOR_TEST
