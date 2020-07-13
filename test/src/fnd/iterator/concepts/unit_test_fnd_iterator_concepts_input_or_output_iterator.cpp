/**
 *	@file	unit_test_fnd_iterator_concepts_input_or_output_iterator.cpp
 *
 *	@brief	input_or_output_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <memory>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_or_output_iterator<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::input_or_output_iterator_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(B, ...)	\
	static_assert(B == bksge::input_or_output_iterator_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace input_or_output_iterator_test
{

BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int      *);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(true,  int const*);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int      * const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, int const* const);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, void*);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, std::unique_ptr<int>);
BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST(false, std::shared_ptr<int>);
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

}	// namespace input_or_output_iterator_test

}	// namespace bksge_iterator_test

#undef BKSGE_INPUT_OR_OUTPUT_ITERATOR_TEST
