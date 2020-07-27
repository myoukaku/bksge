/**
 *	@file	unit_test_fnd_iterator_concepts_input_iterator.cpp
 *
 *	@brief	input_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
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
#  define BKSGE_INPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_iterator<__VA_ARGS__>, "input_iterator");	\
	static_assert(B == bksge::input_iterator_t<__VA_ARGS__>::value, "input_iterator_t")
#else
#  define BKSGE_INPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_iterator_t<__VA_ARGS__>::value, "input_iterator_t")
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

BKSGE_INPUT_ITERATOR_TEST(false, void(A::*)());
BKSGE_INPUT_ITERATOR_TEST(false, int A::*);

BKSGE_INPUT_ITERATOR_TEST(true,  std::array<int, 1>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::array<A, 1>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::deque<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::deque<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::forward_list<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::forward_list<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::list<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::list<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::string::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::string::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::string_view::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  bksge::string_view::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::vector<int>::iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::vector<A>::const_iterator);
BKSGE_INPUT_ITERATOR_TEST(true,  std::istreambuf_iterator<char>);
BKSGE_INPUT_ITERATOR_TEST(false, std::ostreambuf_iterator<char>);

}	// namespace input_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_INPUT_ITERATOR_TEST
