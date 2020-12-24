/**
 *	@file	unit_test_fnd_iterator_concepts_input_iterator.cpp
 *
 *	@brief	input_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/deque.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <streambuf>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_iterator<__VA_ARGS__>, "")
#else
#  define BKSGE_INPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_iterator<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace input_iterator_test
{

struct A {};

BKSGE_INPUT_ITERATOR_TEST(true,  int               *);
BKSGE_INPUT_ITERATOR_TEST(true,  int const         *);
BKSGE_INPUT_ITERATOR_TEST(true,  int       volatile*);
BKSGE_INPUT_ITERATOR_TEST(true,  int const volatile*);
BKSGE_INPUT_ITERATOR_TEST(false, int               * const);
BKSGE_INPUT_ITERATOR_TEST(false, int const         * const);
BKSGE_INPUT_ITERATOR_TEST(false, int       volatile* const);
BKSGE_INPUT_ITERATOR_TEST(false, int const volatile* const);

BKSGE_INPUT_ITERATOR_TEST(true,  int               **);
BKSGE_INPUT_ITERATOR_TEST(true,  int const         **);
BKSGE_INPUT_ITERATOR_TEST(true,  int       volatile**);
BKSGE_INPUT_ITERATOR_TEST(true,  int const volatile**);
BKSGE_INPUT_ITERATOR_TEST(false, int               ** const);
BKSGE_INPUT_ITERATOR_TEST(false, int const         ** const);
BKSGE_INPUT_ITERATOR_TEST(false, int       volatile** const);
BKSGE_INPUT_ITERATOR_TEST(false, int const volatile** const);

BKSGE_INPUT_ITERATOR_TEST(false, void               *);
BKSGE_INPUT_ITERATOR_TEST(false, void const         *);
BKSGE_INPUT_ITERATOR_TEST(false, void       volatile*);
BKSGE_INPUT_ITERATOR_TEST(false, void const volatile*);
BKSGE_INPUT_ITERATOR_TEST(false, void               * const);
BKSGE_INPUT_ITERATOR_TEST(false, void const         * const);
BKSGE_INPUT_ITERATOR_TEST(false, void       volatile* const);
BKSGE_INPUT_ITERATOR_TEST(false, void const volatile* const);

BKSGE_INPUT_ITERATOR_TEST(true,  void               **);
BKSGE_INPUT_ITERATOR_TEST(true,  void const         **);
BKSGE_INPUT_ITERATOR_TEST(true,  void       volatile**);
BKSGE_INPUT_ITERATOR_TEST(true,  void const volatile**);
BKSGE_INPUT_ITERATOR_TEST(false, void               ** const);
BKSGE_INPUT_ITERATOR_TEST(false, void const         ** const);
BKSGE_INPUT_ITERATOR_TEST(false, void       volatile** const);
BKSGE_INPUT_ITERATOR_TEST(false, void const volatile** const);

BKSGE_INPUT_ITERATOR_TEST(false, void(*)());
BKSGE_INPUT_ITERATOR_TEST(false, void(&)());

// Avoid gcc 7 internal compiler error
#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 80000))
BKSGE_INPUT_ITERATOR_TEST(false, void(A::*)());
#endif
BKSGE_INPUT_ITERATOR_TEST(false, int A::*);

BKSGE_INPUT_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::deque<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::deque<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::forward_list<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::forward_list<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::list<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::list<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::string::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::string::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::string_view::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::string_view::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::vector<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::vector<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::istreambuf_iterator<char>);
BKSGE_INPUT_ITERATOR_TEST(false, std::ostreambuf_iterator<char>);

BKSGE_INPUT_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(false, incrementable_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(false, input_or_output_iterator_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(true,  input_iterator_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(false, output_iterator_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(true,  forward_iterator_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(true,  bidirectional_iterator_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>);
BKSGE_INPUT_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace input_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_INPUT_ITERATOR_TEST
