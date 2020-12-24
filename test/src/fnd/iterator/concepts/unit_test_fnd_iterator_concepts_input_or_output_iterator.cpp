/**
 *	@file	unit_test_fnd_iterator_concepts_input_or_output_iterator.cpp
 *
 *	@brief	input_or_output_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <vector>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_or_output_iterator<__VA_ARGS__>, "")
#else
#  define BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_or_output_iterator<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace input_or_output_iterator_test
{

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int               *);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int const         *);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int       volatile*);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int const volatile*);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int               * const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int const         * const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int       volatile* const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int const volatile* const);

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void               *);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const         *);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void       volatile*);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const volatile*);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void               * const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const         * const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void       volatile* const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const volatile* const);

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void               **);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void const         **);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void       volatile**);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  void const volatile**);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void               ** const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const         ** const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void       volatile** const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void const volatile** const);

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, bksge::unique_ptr<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, bksge::shared_ptr<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, std::vector<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  std::vector<int>::iterator);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  std::vector<int>::const_iterator);

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int[]);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int[2]);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int&);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int&&);

struct X
{
	friend auto operator++(X&) -> X&;
	friend auto operator++(X&, int) -> X&;
	using difference_type = int;
};

struct Y
{
	friend auto operator++(Y&) -> Y&;
	friend auto operator++(Y&, int) -> Y;
	friend auto operator*(Y&) -> int;
	using difference_type = int;
};

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X&);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, X const&);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  Y);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, Y&);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, Y const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, Y const&);

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, weakly_incrementable_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, incrementable_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, indirectly_readable_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, indirectly_writable_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  input_or_output_iterator_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  input_iterator_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  output_iterator_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  forward_iterator_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  bidirectional_iterator_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  random_access_iterator_wrapper<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace input_or_output_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST
