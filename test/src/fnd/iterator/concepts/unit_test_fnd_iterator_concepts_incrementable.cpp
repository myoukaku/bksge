/**
 *	@file	unit_test_fnd_iterator_concepts_incrementable.cpp
 *
 *	@brief	incrementable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/incrementable.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <memory>
#include <vector>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == bksge::incrementable<__VA_ARGS__>, "incrementable");	\
	static_assert(B == bksge::incrementable_t<__VA_ARGS__>::value, "incrementable_t")
#else
#  define BKSGE_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == bksge::incrementable_t<__VA_ARGS__>::value, "incrementable_t")
#endif

namespace bksge_iterator_test
{

namespace incrementable_test
{

BKSGE_INCREMENTABLE_TEST(true,  int               *);
BKSGE_INCREMENTABLE_TEST(true,  int const         *);
BKSGE_INCREMENTABLE_TEST(true,  int       volatile*);
BKSGE_INCREMENTABLE_TEST(true,  int const volatile*);
BKSGE_INCREMENTABLE_TEST(false, int               * const);
BKSGE_INCREMENTABLE_TEST(false, int const         * const);
BKSGE_INCREMENTABLE_TEST(false, int       volatile* const);
BKSGE_INCREMENTABLE_TEST(false, int const volatile* const);

BKSGE_INCREMENTABLE_TEST(false, void               *);
BKSGE_INCREMENTABLE_TEST(false, void const         *);
BKSGE_INCREMENTABLE_TEST(false, void       volatile*);
BKSGE_INCREMENTABLE_TEST(false, void const volatile*);
BKSGE_INCREMENTABLE_TEST(false, void               * const);
BKSGE_INCREMENTABLE_TEST(false, void const         * const);
BKSGE_INCREMENTABLE_TEST(false, void       volatile* const);
BKSGE_INCREMENTABLE_TEST(false, void const volatile* const);

BKSGE_INCREMENTABLE_TEST(false, std::unique_ptr<int>);
BKSGE_INCREMENTABLE_TEST(false, std::shared_ptr<int>);
BKSGE_INCREMENTABLE_TEST(false, std::vector<int>);
BKSGE_INCREMENTABLE_TEST(true,  std::vector<int>::iterator);
BKSGE_INCREMENTABLE_TEST(true,  std::vector<int>::const_iterator);
BKSGE_INCREMENTABLE_TEST(true,  std::istream_iterator<int>);
BKSGE_INCREMENTABLE_TEST(false, std::ostream_iterator<int>);

BKSGE_INCREMENTABLE_TEST(false, int[]);
BKSGE_INCREMENTABLE_TEST(false, int[2]);
BKSGE_INCREMENTABLE_TEST(false, int&);
BKSGE_INCREMENTABLE_TEST(false, int&&);

struct X
{
	friend auto operator++(X&)->X&;
	friend auto operator++(X&, int)->X&;
	using difference_type = int;
};

struct Y
{
	friend auto operator++(Y&)->Y&;
	friend auto operator++(Y&, int)->Y; // prvalueを返す必要がある
	friend bool operator==(const Y&, const Y&);
	friend bool operator!=(const Y&, const Y&);
	using difference_type = int;
};

BKSGE_INCREMENTABLE_TEST(false, X);
BKSGE_INCREMENTABLE_TEST(false, X&);
BKSGE_INCREMENTABLE_TEST(false, X const);
BKSGE_INCREMENTABLE_TEST(false, X const&);
BKSGE_INCREMENTABLE_TEST(true,  Y);
BKSGE_INCREMENTABLE_TEST(false, Y&);
BKSGE_INCREMENTABLE_TEST(false, Y const);
BKSGE_INCREMENTABLE_TEST(false, Y const&);

BKSGE_INCREMENTABLE_TEST(false, weakly_incrementable_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(true,  incrementable_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(false, indirectly_readable_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(false, indirectly_writable_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(false, input_or_output_iterator_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(false, input_iterator_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(false, output_iterator_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(true,  forward_iterator_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(true,  bidirectional_iterator_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(true,  random_access_iterator_wrapper<int>);
BKSGE_INCREMENTABLE_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace incrementable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INCREMENTABLE_TEST
