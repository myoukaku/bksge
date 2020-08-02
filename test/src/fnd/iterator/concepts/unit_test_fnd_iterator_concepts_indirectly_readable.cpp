/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_readable.cpp
 *
 *	@brief	indirectly_readable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <memory>
#include <vector>
#include <streambuf>
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_READABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_readable<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECTLY_READABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_readable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirectly_readable_test
{

BKSGE_INDIRECTLY_READABLE_TEST(true,  int               *);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int const         *);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int       volatile*);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int const volatile*);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int               * const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int const         * const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int       volatile* const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  int const volatile* const);

BKSGE_INDIRECTLY_READABLE_TEST(false, void               *);
BKSGE_INDIRECTLY_READABLE_TEST(false, void const         *);
BKSGE_INDIRECTLY_READABLE_TEST(false, void       volatile*);
BKSGE_INDIRECTLY_READABLE_TEST(false, void const volatile*);
BKSGE_INDIRECTLY_READABLE_TEST(false, void               * const);
BKSGE_INDIRECTLY_READABLE_TEST(false, void const         * const);
BKSGE_INDIRECTLY_READABLE_TEST(false, void       volatile* const);
BKSGE_INDIRECTLY_READABLE_TEST(false, void const volatile* const);

BKSGE_INDIRECTLY_READABLE_TEST(true,  void               **);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void const         **);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void       volatile**);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void const volatile**);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void               ** const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void const         ** const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void       volatile** const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  void const volatile** const);

BKSGE_INDIRECTLY_READABLE_TEST(true,  std::unique_ptr<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  std::shared_ptr<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, std::vector<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  std::vector<int>::iterator);
BKSGE_INDIRECTLY_READABLE_TEST(true,  std::vector<int>::const_iterator);
BKSGE_INDIRECTLY_READABLE_TEST(true,  std::istream_iterator<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, std::ostream_iterator<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  std::istreambuf_iterator<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, std::ostreambuf_iterator<int>);

BKSGE_INDIRECTLY_READABLE_TEST(false, int[]);
BKSGE_INDIRECTLY_READABLE_TEST(false, int[2]);
BKSGE_INDIRECTLY_READABLE_TEST(false, int&);
BKSGE_INDIRECTLY_READABLE_TEST(false, int&&);

struct X
{
	using value_type = char*;
};
struct Y
{
	char* const& operator*() const;
};
struct Z
{
	using value_type = char*;
	char* const& operator*() const;
};

BKSGE_INDIRECTLY_READABLE_TEST(false, X);
BKSGE_INDIRECTLY_READABLE_TEST(false, X&);
BKSGE_INDIRECTLY_READABLE_TEST(false, X const);
BKSGE_INDIRECTLY_READABLE_TEST(false, X const&);
BKSGE_INDIRECTLY_READABLE_TEST(false, Y);
BKSGE_INDIRECTLY_READABLE_TEST(false, Y&);
BKSGE_INDIRECTLY_READABLE_TEST(false, Y const);
BKSGE_INDIRECTLY_READABLE_TEST(false, Y const&);
BKSGE_INDIRECTLY_READABLE_TEST(true,  Z);
BKSGE_INDIRECTLY_READABLE_TEST(true,  Z&);
BKSGE_INDIRECTLY_READABLE_TEST(true,  Z const);
BKSGE_INDIRECTLY_READABLE_TEST(true,  Z const&);

BKSGE_INDIRECTLY_READABLE_TEST(false, weakly_incrementable_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, incrementable_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  indirectly_readable_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, indirectly_writable_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, input_or_output_iterator_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  input_iterator_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(false, output_iterator_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  forward_iterator_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  bidirectional_iterator_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  random_access_iterator_wrapper<int>);
BKSGE_INDIRECTLY_READABLE_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace indirectly_readable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_READABLE_TEST
